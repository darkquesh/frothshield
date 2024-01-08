#ifndef INC_I2C_SCANNER_H_
#define INC_I2C_SCANNER_H_

#include <stdio.h>
#include "main.h"

int scan_i2c(UART_HandleTypeDef* huart, I2C_HandleTypeDef* hi2c);

#endif /* INC_I2C_SCANNER_H_ */
