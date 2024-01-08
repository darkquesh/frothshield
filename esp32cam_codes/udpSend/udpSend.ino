// Load Wi-Fi library
#include <WiFi.h>
#include <WiFiUdp.h>
#include "string.h"

// Temperature data
String tempSensor;
uint8_t tempSensorBuf[50] = "hello world!";
//char tempSensor[50];

// Replace with your network credentials
const char* ssid = "";
const char* password = "";

// Mobile hotspot
IPAddress local_IP(192, 168, 200, 184);
// Set your Gateway IP address
IPAddress gateway(192, 168, 200, 218);
IPAddress subnet(255, 255, 255, 0);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

// UDP
WiFiUDP udp;
const int udpPort = 44444;

void setup() {
  Serial.begin(115200);
  //SerialPort.begin(115200, SERIAL_8N1, RXD, TXD);
  delay(100);

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  udp.begin(udpPort);
}

// the loop function runs over and over again forever
void loop() {
  tempSensor = Serial.readString();
  tempSensor.trim();

  // (String) to (uint8_t*) conversion
  tempSensor.getBytes(tempSensorBuf, 50);

  //uint8_t buffer[50] = "hello world";

  //This initializes udp and transfer buffer
  udp.beginPacket(udp.remoteIP(), udp.remotePort());
  udp.write(tempSensorBuf, 15);
  udp.endPacket();
  memset(tempSensorBuf, 0, 50);
  //processing incoming packet, must be called before reading the buffer
  udp.parsePacket();
  //receive response from server, it will be HELLO WORLD
  if(udp.read(tempSensorBuf, 50) > 0){
    Serial.print("Server to client: ");
    Serial.print((char *)tempSensorBuf);
  }
  
  delay(1);
}

