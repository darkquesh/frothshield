/*
 * @file:	DS18B20.h
 *
 * @description: Library for interfacing
 * DS18B20 temperature sensor
 *
 */

#include "stm32l4xx_hal.h"
#include <stdint.h>

#include "Timing.h"


typedef struct {
    TIMER *tim;
} DS18B20;

void DS18B20_Init(DS18B20 *sensor, TIMER *tim);
float DS18B20_readTemperature(DS18B20 *sensor);

void DS18B20_setDataPin(DS18B20 *sensor, int on);
void DS18B20_toggleDataPin(DS18B20 *sensor);

void DS18B20_setPinOUTPUT(DS18B20 *sensor);
void DS18B20_setPinINPUT(DS18B20 *sensor);

void DS18B20_startSensor(DS18B20 *sensor);

void DS18B20_writeData(DS18B20 *sensor, uint8_t data);
uint8_t DS18B20_readData(DS18B20 *sensor);
