/*
 * uart.c
 *
 *  Created on: Mar 24, 2021
 *      Author: jongb
 */
//#include <../Inc/stm32g071xx.h>
#include "uart.h"

void UART_Config(void)
{

	RCC->APBENR1 |= (1 << 18);	//enable clock for USART3
	RCC->IOPENR |= (1 << 3);	//enable clock for GPIO PORT D. (Using PD8 for Transmit, PD9 for Receive)

	GPIOD->OSPEEDR |= (1 << 16);	//set output speed to LOW on PD8
	GPIOD->OSPEEDR |= (1 << 18);	//set output speed to LOW on PD9

	GPIOD->MODER |= (1 << 17); //alternate function on PD8
	GPIOD->MODER &= ~(1 << 16);
	GPIOD->MODER &= ~(1 << 18);//alternate function on PD9

	GPIOD->AFR[1] |= 0x0; // set AFO in AFRH register to use USART3_TX for PD8
	GPIOD->AFR[1] |= (0 << 4); // set AFO in AFRH register to use USART3_RX for PD9

	USART3->CR1 &= ~(1 << 0); //disable USART3 to allow changes to registers

	USART3->CR1 &= ~(1 << 28);	//program M bits, set word length to 8 bits
	USART3->CR1 &= ~(1 << 12);
	USART3->CR1 &= ~(1 << 15);	//oversampling by 16
	USART3->BRR |= 0x1A1;	//set the baud rate to 38400. PCLK default = 16MHz -> (16000000/38400) = 0x1A1. See reference manual on calculation.
	USART3->CR2 &= ~(3 << 12) ;	// program number of stop bits (1)

	USART3->CR1 |= (1 << 0);	//enable USART3
	USART3->CR1 |= (1 << 2); //Enable Receive for USART3
	USART3->CR1 |= (1 << 3); //Enable Transmission for USART3
	USART3->CR1 |= (1 << 5); //RXFIFO not empty interrupt available (USART interrupt generated whenever RXFNE = 1, or ORE =1 )
}

//Send a string through UART2
void UART_SendString ( char* s )
{
	while(*s != 0)
		{
			USART3->TDR = *s; // load the data into USART3_TDR, also clears TC bit in USART3_ISR.
			while (!(USART3->ISR & (1<<6)));  // Wait until transmission complete (TC = 1)
			s++;
		}
}

void UART_SendChar (char c)
{
	USART3->TDR = c;
	while (!(USART3->ISR & (1<<6)));
}


char UART_ReceiveChar( void )
{
	char receive_buffer = USART3->RDR;
	while(USART3->ISR & (1 << 5));//wait for RXNE flag is cleared. (RXFIFO is empty)
	return receive_buffer;
}


