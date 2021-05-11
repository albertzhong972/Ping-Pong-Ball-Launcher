/*
 * PWM.c
 *
 *  Created on: May 2, 2021
 *      Author: jongb
 */

#include "PWM.h"
//configure TIM3 for 20ms PWM
void PWM_Config(void)
{

	RCC->APBENR1 |= (1 << 0);	//enable clock for TIM2
	TIM2->PSC = 0;	//Prescaler Value
	TIM2->ARR = 320000;	//Reload Value (PWM period = reload value / timer clock frequency). Default clock frequency = 16MHz

	//motor 1 (TIM2 Channel 1)
	TIM2->CCR1 = 16000;	//Adjust Duty Cycle (initial duty cycle is 5%)
	TIM2->CCMR1 |= (6 << 4);	//PWM mode 1
	TIM2->CCER |= (1 << 0);	//Capture/Compare 1 Output Enabled

	//motor 2 (TIM2 Channel 2)
	TIM2->CCER |= (1 << 4);	//Capture/Compare 2 Output Enabled
	TIM2->CCMR1 |= (6 << 12);	//PWM mode 1
	TIM2->CCR2 = 16000;	//Adjust Duty Cycle (initial duty cycle is 5%)

	TIM2->CR1 |= TIM_CR1_CEN;	//enable counter for TIM2

}


void motor1_PWM(double dutycycle) {
	double x;
	if((dutycycle >= 0) && (dutycycle <= 100))
	{
		x = dutycycle / 100;
		TIM2->CCR1 = (TIM2->ARR * x);
	}
}

void motor2_PWM(double dutycycle) {
	double x;
	if((dutycycle >= 0) && (dutycycle <= 100))
	{
		x = dutycycle / 100;
		TIM2->CCR2 = (TIM2->ARR * x);
	}
}
