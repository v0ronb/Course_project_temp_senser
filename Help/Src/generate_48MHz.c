/*
 * generate_48MHz.c
 *
 *  Created on: 27 нояб. 2021 г.
 *      Author: Владимир
 */

#include "generate_48MHz.h"

// generation to 48 MHz
void clock48Mhz_init() {
	RCC->CR &= ~RCC_CR_PLLON;
	while(RCC->CR & RCC_CR_PLLRDY);

	RCC->CFGR |= RCC_CFGR_PLLMUL12;

	RCC->CR |= RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);
		RCC->CFGR |= RCC_CFGR_SW_1;	//as PLL
		SystemCoreClockUpdate();
}
