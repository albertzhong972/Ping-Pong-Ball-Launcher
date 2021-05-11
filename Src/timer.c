/*
 * timer.c
 *
 *  Created on: May 2, 2021
 *      Author: jongb
 */
#include "timer.h"

void Timer_Config(void)
{
	RCC->APBENR1 |= (1 << 4);	//enable clock for TIM6

	//TIM6->PSC = 16-1;	//Prescaler Value , timer bus runs at 16 MHz, 16Mhz / 16 = 1 us
	//TIM6->ARR = 0xFFFF;	//Reload Value = max

	TIM6->PSC = 16-1;	//Prescaler Value , timer bus runs at 16 MHz, 16Mhz / 16 = 1 us
	TIM6->ARR = 1800;	//Reload Value
	TIM6->DIER |= (1 << 0); //enable interrupt
	TIM6->CR1 |= TIM_CR1_CEN;	//enable counter for TIM6


	while (!(TIM6->SR & (1<<0))); //wait for registers to update
}

void Delay_us (uint16_t us)
{
	TIM6->CNT = 0;
	while (TIM6->CNT < us);
}

void Delay_ms (uint16_t ms)
{
	for (uint16_t i=0; i<ms; i++)
	{
		Delay_us (1000); // delay of 1 ms
	}
}
