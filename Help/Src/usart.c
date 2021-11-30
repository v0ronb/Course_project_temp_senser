/*
 * usart.c
 *
 *  Created on: 17 окт. 2021 г.
 *      Author: Владимир
 */
#include "usart.h"

uint32_t usart_array[SIZE_TEMP];


void usart_gpio_init(){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN; //GPIOA clocking
	GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1; //AF config for USART2
	GPIOA->AFR[0] |= (1<<8) | (1<<12); //AF select for pins 2, 3
}



void usart_init(){
	usart_gpio_init();
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; //USART2 clocking
	USART2->BRR = SystemCoreClock/ BAUD; //transm speed = 38.4 kBps
	USART2->CR3 |= USART_CR3_DMAT;
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; //transm and receive en
	USART2->CR3 |= USART_CR3_OVRDIS; //dis overrun error

	while ((USART2->ISR & USART_ISR_TC) != USART_ISR_TC){}
	USART2->ICR |= USART_ICR_TCCF; //clear TC flag
	USART2->CR1 |= USART_CR1_UE; //USART2 enable

	dma_usart2_tx(usart_array, SIZE_TEMP);

}

void usart_start(){
	DMA1_Channel4->CCR &=~DMA_CCR_EN;
	DMA1_Channel4->CMAR = (uint32_t)(&usart_array[0]);
	DMA1_Channel4->CNDTR = SIZE_TEMP;
	DMA1_Channel4->CCR |=DMA_CCR_EN;

}

void send_data(float temperature){
	uint32_t whole_part = temperature*100;
	usart_array[0]=(uint32_t)temperature;
	usart_array[1]=(uint32_t)(whole_part%100);
	usart_start();
}

