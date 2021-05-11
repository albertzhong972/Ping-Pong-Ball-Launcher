/*
 * stepper.c
 *
 *  Created on: May 2, 2021
 *      Author: jongb
 */

#include "stepper.h"

int Steps = 0;
int Direction = 1; //stepper motor rotates counter-clockwise

void SetDirection() {
  if (Direction == 1) {
    Steps++;
  }
  if (Direction == 0) {
    Steps--;
  }
  if (Steps > 3) {
    Steps = 0;
  }
  if (Steps < 0) {
    Steps = 3;
  }
}


void stepper(int xw) {
	for (int x = 0; x < xw; x++) {
	    switch (Steps) {
	      case 0:
	    	  GPIOA->ODR &= ~(1 << 5); // IN1 = LOW
	    	  GPIOA->ODR &= ~(1 << 6); // IN2 = LOW
	    	  GPIOA->ODR |= (1 << 7);  // IN3 = HIGH
	    	  GPIOB->ODR |= (1 << 0);  // IN4 = HIGH

	        break;
	      case 1:
	    	  GPIOA->ODR &= ~(1 << 5); // IN1 = LOW
	    	  GPIOA->ODR |= (1 << 6);  // IN2 = HIGH
	    	  GPIOA->ODR |= (1 << 7);  // IN3 = HIGH
	    	  GPIOB->ODR &= ~(1 << 0); // IN4 = LOW

	        break;
	      case 2:
	    	  GPIOA->ODR |= (1 << 5);  // IN1 = HIGH
	    	  GPIOA->ODR |= (1 << 6);  // IN2 = HIGH
	    	  GPIOA->ODR &= ~(1 << 7); // IN3 = LOW
	    	  GPIOB->ODR &= ~(1 << 0); // IN4 = LOW

	        break;
	      case 3:
	    	  GPIOA->ODR |= (1 << 5);  // IN1 = HIGH
	    	  GPIOA->ODR &= ~(1 << 6); // IN2 = LOW
	    	  GPIOA->ODR &= ~(1 << 7); // IN3 = LOW
	    	  GPIOB->ODR |= (1 << 0);  // IN4 = HIGH

	        break;

	      default:
	    	  GPIOA->ODR &= ~(1 << 5); // IN1 = LOW
	    	  GPIOA->ODR &= ~(1 << 6); // IN2 = LOW
	    	  GPIOA->ODR &= ~(1 << 7); // IN3 = LOW
	    	  GPIOB->ODR &= ~(1 << 0); // IN4 = LOW

	        break;
	    }
	    SetDirection();
	  }
}

