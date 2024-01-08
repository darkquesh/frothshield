#include "Timing.h"


void TIMER_Init(TIMER* timer, TIM_HandleTypeDef* tim)
{
    timer->_tim = tim;
    HAL_TIM_Base_Start(timer->_tim);
    //HAL_TIM_Base_Start_IT(timer->_tim);
}

void TIMER_delayUS(TIMER* timer, volatile uint16_t us)
{
    //__disable_irq();
	timer->_tim->Instance->PSC = 80-1;
    timer->_tim->Instance->CNT = 0;
    while (timer->_tim->Instance->CNT < us);
    //__enable_irq();
}

void TIMER_delayMS(TIMER* timer, volatile uint16_t ms)
{
	volatile uint16_t delay = 10*ms;
	timer->_tim->Instance->PSC = 8000-1;
	timer->_tim->Instance->CNT = 0;
	//volatile uint16_t start = timer->_tim->Instance->CNT;
	while (timer->_tim->Instance->CNT < delay);
	//while ((timer->_tim->Instance->CNT - start) < delay);
}
