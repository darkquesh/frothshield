/*
 * i2c_scanner.c
 *
 *  Created on: Dec 23, 2023
 *      Author: erenk
 */

/*-[ I2C Bus Scanning ]-*/

#include "i2c_scanner.h"

int scan_i2c(UART_HandleTypeDef* huart, I2C_HandleTypeDef* hi2c)
{
	uint8_t Buffer[25] = {0};
	uint8_t Space[] = " - ";
	uint8_t StartMSG[] = "Starting I2C Scanning: \r\n";
	uint8_t EndMSG[] = "Done! \r\n\r\n";

	uint8_t i = 0, ret;

    HAL_UART_Transmit(huart, StartMSG, sizeof(StartMSG), 10000);
    for(i=1 ; i<128; i++)
    {
        ret = HAL_I2C_IsDeviceReady(hi2c, (uint16_t)(i<<1), 3, 5);
        if (ret != HAL_OK) /* No ACK Received At That Address */
        {
            HAL_UART_Transmit(huart, Space, sizeof(Space), 10000);
            //return ret;
        }
        else if(ret == HAL_OK)
        {
            sprintf((char*)Buffer, "0x%X", i);
            HAL_UART_Transmit(huart, Buffer, sizeof(Buffer), 10000);
        }
    }
    HAL_UART_Transmit(huart, EndMSG, sizeof(EndMSG), 10000);

    return ret;
}
