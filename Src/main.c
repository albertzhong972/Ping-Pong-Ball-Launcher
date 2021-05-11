/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Albert Zhong
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <../Inc/stm32g071xx.h>
#include "timer.h"
#include "stepper.h"
#include "PWM.h"
#include "uart.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

//GPIO config for stepper motor
void GPIO_Config ( void )
{

	RCC->IOPENR |= (1 << 0); //enable Ports A, B, and C
	RCC->IOPENR |= (1 << 1);
	RCC->IOPENR |= (1 << 2);

	//GPIO for stepper motors
	GPIOA->MODER &= ~(1 << 11); // PA5, 6, 7 are outputs
	GPIOA->MODER &= ~(1 << 13);
	GPIOA->MODER &= ~(1 << 15);
	GPIOB->MODER &= ~(1 << 1);  //PB0 is output

	//PWM
	GPIOA->MODER &= ~(1 << 0);	//alternate function on PA0
	GPIOA->AFR[0] |= (2 << 0);	//use AF2 on PA0 (TIM2_CH1_ETR)

	GPIOA->MODER &= ~(1 << 2);	//alternate function on PA1
	GPIOA->AFR[0] |= (2 << 4);	//use AF2 on PA1 (TIM2_CH2)

}


//timer interrupt to run stepper motor in the background (runs every 1800us)
void TIM6_DAC_LPTIM1_IRQHandler (void) {

	  if (TIM6->SR & TIM_SR_UIF)
	  {
		  TIM6->SR &= ~(TIM_SR_UIF);
		  stepper(1);
	  }
}

double motor1_duty_cycle = 5; //off: 5, full speed: 10
double motor2_duty_cycle = 5;

/*
* USART interrupt when data is received from HC-05 Bluetooth module
* Used to turn on/off and control speed of the brushless motors
*/
void USART3_USART4_LPUART1_IRQHandler (void) {
	char rxb = UART_ReceiveChar();
	switch (rxb) {
		case '0' : //turn off brushless motors
			motor1_duty_cycle = 5;
			motor2_duty_cycle = 5;
			break;

		case '1' : //turn on brushless motors
			motor1_duty_cycle = 5.35;
			motor2_duty_cycle = 5.35;
			break;

		case '2' : //increase duty cycle slightly
			motor1_duty_cycle += 0.05;
			motor2_duty_cycle += 0.05;
			break;

		case '3' : //decrease duty cycle slightly
			motor1_duty_cycle -= 0.05;
			motor2_duty_cycle -= 0.05;
			break;

		case '4' : //topspin setting
			motor1_duty_cycle = 5.55;
			motor2_duty_cycle = 5;
			break;

		case '5' : //backspin setting
			motor1_duty_cycle = 5;
			motor2_duty_cycle = 5.55;
			break;

		default:
			motor1_duty_cycle = 5;
			motor2_duty_cycle = 5;
			break;
	}

}


int main(void) {

	GPIO_Config();
	PWM_Config();
	UART_Config();
	Timer_Config();

	NVIC_SetPriority(TIM6_DAC_LPTIM1_IRQn, 0x03); //Timer 6 interrupt (stepper motor)
	NVIC_EnableIRQ(TIM6_DAC_LPTIM1_IRQn);

	NVIC_SetPriority(USART3_4_LPUART1_IRQn, 0x04); //USART RX interrupt (bluetooth module)
	NVIC_EnableIRQ(USART3_4_LPUART1_IRQn);


	while(1) {

		motor1_PWM(motor1_duty_cycle); //run the brushless motors at the desired duty cycle
		motor2_PWM(motor2_duty_cycle);

		//ensure duty cycle isn't too high or low
		if(motor1_duty_cycle > 5.7)
		{
			motor1_duty_cycle = 5.7;
		}
		if(motor2_duty_cycle > 5.7)
		{
			motor2_duty_cycle = 5.7;
		}

		if(motor1_duty_cycle < 5)
		{
			motor1_duty_cycle = 5;
		}
		if(motor2_duty_cycle < 5)
		{
			motor2_duty_cycle = 5;
		}
	}

}
