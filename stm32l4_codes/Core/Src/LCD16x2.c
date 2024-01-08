/*
 * LCD16x2.c
 *
 *  Created on: Dec 23, 2023
 *      Author: erenk
 */

#include "LCD16x2.h"

//
void lcd_write_nibble(I2C_HandleTypeDef* hi2c, uint8_t nibble, uint8_t rs)
{
	uint8_t backlight_state = lcd_backlight(1);

	uint8_t data = nibble << D4_BIT;
	data |= rs << RS_BIT;
	data |= backlight_state << BL_BIT; // Include backlight state in data
	data |= 1 << EN_BIT;
	HAL_I2C_Master_Transmit(hi2c, LCD_I2C_ADDR << 1, &data, 1, 100);
	HAL_Delay(1);
	data &= ~(1 << EN_BIT);
	HAL_I2C_Master_Transmit(hi2c, LCD_I2C_ADDR << 1, &data, 1, 100);
}

//
void lcd_send_cmd(I2C_HandleTypeDef* hi2c, uint8_t cmd)
{
	uint8_t upper_nibble = cmd >> 4;
	uint8_t lower_nibble = cmd & 0x0F;
	lcd_write_nibble(hi2c, upper_nibble, 0);
	lcd_write_nibble(hi2c, lower_nibble, 0);

	if (cmd == 0x01 || cmd == 0x02)
		HAL_Delay(2);

	/*
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit(hi2c, LCD_I2C_ADDR << 1, (uint8_t *)data_t, 4, 100);*/
}

//
void lcd_send_data(I2C_HandleTypeDef* hi2c, uint8_t data)
{
	uint8_t upper_nibble = data >> 4;
	uint8_t lower_nibble = data & 0x0F;
	lcd_write_nibble(hi2c, upper_nibble, 1);
	lcd_write_nibble(hi2c, lower_nibble, 1);

	/*
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1
	data_t[1] = data_u|0x09;  //en=0, rs=1
	data_t[2] = data_l|0x0D;  //en=1, rs=1
	data_t[3] = data_l|0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit(hi2c, LCD_I2C_ADDR << 1, (uint8_t *)data_t, 4, 100);
	*/
}

//
void lcd_init(I2C_HandleTypeDef* hi2c)
{
	HAL_Delay(50);
	lcd_write_nibble(hi2c, 0x03, 0);
	HAL_Delay(5);
	lcd_write_nibble(hi2c, 0x03, 0);
	HAL_Delay(1);
	lcd_write_nibble(hi2c, 0x03, 0);
	HAL_Delay(1);
	lcd_write_nibble(hi2c, 0x02, 0);

	lcd_send_cmd(hi2c, 0x28);
	lcd_send_cmd(hi2c, 0x0C);
	lcd_send_cmd(hi2c, 0x06);
	lcd_send_cmd(hi2c, 0x01);

	HAL_Delay(2);

	/*
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (hi2c, 0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (hi2c, 0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (hi2c, 0x30);
	HAL_Delay(10);
	lcd_send_cmd (hi2c, 0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	lcd_send_cmd (hi2c, 0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (hi2c, 0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (hi2c, 0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (hi2c, 0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (hi2c, 0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
	*/
}

//
void lcd_write_string(I2C_HandleTypeDef* hi2c, char *str)
{
	while (*str)
		lcd_send_data(hi2c, *str++);
}

//
void lcd_set_cursor(I2C_HandleTypeDef* hi2c, uint8_t row, uint8_t column)
{
	uint8_t address;
	switch (row) {
		case 0:
			address = 0x00;
			break;
		case 1:
			address = 0x40;
			break;
		default:
			address = 0x00;
	}
	address += column;
	lcd_send_cmd(hi2c, 0x80 | address);
}

//
void lcd_clear(I2C_HandleTypeDef* hi2c)
{
	lcd_send_cmd(hi2c, 0x01);
    HAL_Delay(2);
}

//
uint8_t lcd_backlight(uint8_t state)
{
	uint8_t backlight_state = 0;

	if (state)
		backlight_state = 1;
	else
		backlight_state = 0;

	return backlight_state;
}
