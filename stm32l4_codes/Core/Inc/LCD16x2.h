/*
 * @file:	LCD16x2.h
 *
 * @description: I2C library for a 16x2 LCD display module
 * 				 Hitachi HD44780 controller based 16×2 LCD
 * 				 module with a PCF8574 I2C interface
 *
 * @notice:		 Slowly turn the blue screw in the I2C with a screw driver!!
 */

#ifndef INC_LCD16X2_H_
#define INC_LCD16X2_H_

#include "main.h"

#define LCD_I2C_ADDR 0x27 // I2C address of the PCF8574
#define RS_BIT 0 // Register select bit
#define EN_BIT 2 // Enable bit
#define BL_BIT 3 // Backlight bit
#define D4_BIT 4 // Data 4 bit
#define D5_BIT 5 // Data 5 bit
#define D6_BIT 6 // Data 6 bit
#define D7_BIT 7 // Data 7 bit

#define LCD_ROWS 2 // Number of rows on the LCD
#define LCD_COLS 16 // Number of columns on the LCD


// Function prototypes

/*
 * lcd_write_nibble(I2C_HandleTypeDef* hi2c, uint8_t nibble, uint8_t rs)
 * Sends a 4-bit nibble of data to the LCD display through the PCF8574 I2C I/O expander.
 */
void lcd_write_nibble(I2C_HandleTypeDef* hi2c, uint8_t nibble, uint8_t rs);

/*
 * lcd_send_cmd(I2C_HandleTypeDef* hi2c, uint8_t cmd)
 * Sends a command to the LCD display
 */
void lcd_send_cmd(I2C_HandleTypeDef* hi2c, uint8_t cmd);

/*
 * lcd_send_data(I2C_HandleTypeDef* hi2c, uint8_t data)
 * Sends data to the LCD display
*/
void lcd_send_data(I2C_HandleTypeDef* hi2c, uint8_t data);

/*
 * lcd_init()
 * Initializes the LCD display
 */
void lcd_init();

/*
 * lcd_write_string(I2C_HandleTypeDef* hi2c, char *str)
 * Writes a null-terminated string to the LCD display
 */

void lcd_write_string(I2C_HandleTypeDef* hi2c, char *str);

/*
 * lcd_set_cursor(I2C_HandleTypeDef* hi2c, uint8_t row, uint8_t column)
 * Sets the cursor position on the LCD display
 */
void lcd_set_cursor(I2C_HandleTypeDef* hi2c, uint8_t row, uint8_t column);

/*
 * lcd_clear(I2C_HandleTypeDef* hi2c)
 * Clears the display
 */
void lcd_clear(I2C_HandleTypeDef* hi2c);

/*
 * lcd_backlight(uint8_t state)
 * Turns the backlight of the LCD on or off
 */
uint8_t lcd_backlight(uint8_t state);

#endif /* INC_LCD16X2_H_ */
