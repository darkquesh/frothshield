import socket
import os

import matplotlib.pyplot as plt
import matplotlib.animation as animation

your_path = ""
os.chdir(your_path)

#UDP_IP = "192.168.1.184"     # ESP32 IP
UDP_IP = "192.168.200.184"   # for mobile hotspot
SHARED_UDP_PORT = 44444
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
sock.connect((UDP_IP, SHARED_UDP_PORT))

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []     # Store time here (seconds)
ys = []     # Store sensor temperature here (celsius)
rs = []     # For theoretical values

def loop(i, xs, ys):
    #while True:
    data = sock.recv(2048)

    with open('udp_temp_log.txt', 'a') as f:
        f.write(data.decode())
        f.write('\n')
        f.close()

    #print(data.decode())

    try:
        # This function is called periodically from FuncAnimation
        line = data.decode()      # ASCII
        line_as_list = line.split(',')
        i = int(line_as_list[0])

        relProb = line_as_list[1]
        relProb_as_list = relProb.split('\x00')
        relProb_float = float(relProb_as_list[0])

        print(f"{i} | {relProb_float}°C")
        
        # Add x and y to lists
        xs.append(i)
        ys.append(relProb_float)
        rs.append(0.5)


        #print(ys)

        # Limit x and y lists to 20 items
        #xs = xs[-20:]
        #ys = ys[-20:]

        # Draw x and y lists
        ax.clear()
        ax.plot(xs, ys, label="Experimental")
        #ax.plot(xs, rs, label="Theoretical")

        # Format plot
        plt.xticks(rotation=45, ha='right')
        plt.subplots_adjust(bottom=0.20)
        plt.title('DS18B20 temperature sensor')
        plt.xlabel('Time (s)')
        plt.ylabel('Temperature (°C)')
        plt.grid()
        #plt.legend()
        #plt.axis([1, None, 0, 1.1])    # Use for arbitrary number of trials
        #plt.axis([1, 100, 0, 1.1])     # Use for 100 trial demo
        
        if len(xs) > 1:
            if xs[-1] < xs[-2]:
                raise Exception

    except Exception:
        print("Board reset!")
        ax.clear()
        xs.clear()
        ys.clear()
        rs.clear()
        with open('udp_temp_log.txt', 'a') as f:
            f.write('\n')
            f.close()

if __name__ == "__main__":
    sock.send('Hello ESP32'.encode())
    # Set up plot to call animate() function periodically

    reset = True

    if reset:
        sock.send("RST".encode())

    ani = animation.FuncAnimation(fig, loop, fargs=(xs, ys), interval=1000)
    plt.show()

    #loop()