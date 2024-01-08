#pragma once
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"

typedef struct {
    TIM_HandleTypeDef* _tim;
} TIMER;

void TIMER_Init(TIMER* timer, TIM_HandleTypeDef* tim);
void TIMER_delayUS(TIMER* timer, volatile uint16_t us);
void TIMER_delayMS(TIMER* timer, volatile uint16_t ms);
