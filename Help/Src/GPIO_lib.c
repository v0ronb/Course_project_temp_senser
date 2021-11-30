/*
 * GPIO_lib.c
 *
 *  Created on: 13 нояб. 2021 г.
 *      Author: Владимир
 */

#include "GPIO_lib.h"

void GPIO_config(){
	//takt on
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;	// tackt GPIO
	GPIOC->MODER |= GPIO_MODER_MODER0;	//analog
}

void GPIO_DHT11_init(){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER|=GPIO_MODER_MODER13_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR13_0;//pull up - 01, pull down - 10
}

void InitGPIO_RCC(GPIO_TypeDef *GPIO) {
	if (GPIO == GPIOA) {
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	}
	else if (GPIO == GPIOB) {
		RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	}
	else if (GPIO == GPIOC) {
		RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	}
	else if (GPIO == GPIOD) {
		RCC->AHBENR |= RCC_AHBENR_GPIODEN;
	}
}

void InitGPIO_led(){

	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER8_0;
}
