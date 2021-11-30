/*
 * dma.c
 *
 *  Created on: 12 нояб. 2021 г.
 *      Author: Владимир
 */

#include "dma.h"

void DMA1_CH1_IRQHandler(){
	DMA1->IFCR |= DMA_IFCR_CTCIF1;
	ADC1->CR |= ADC_CR_ADSTP; //Stop work ADC
}


//init_chanel DMA for ADC
void dma_adc(uint16_t *array_adc, uint8_t size){

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel1->CPAR = (uint32_t)(&ADC1->DR);
	DMA1_Channel1->CMAR = (uint32_t)(array_adc);
	DMA1_Channel1->CNDTR = size;
	DMA1_Channel1->CCR |= DMA_CCR_PL_1;
	DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0;
	DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0; //16 bit
	DMA1_Channel1->CCR |= DMA_CCR_MINC;
	SYSCFG->CFGR1 &= ~SYSCFG_CFGR1_ADC_DMA_RMP; //needed for ADC requests

	DMA1_Channel1->CCR |= DMA_CCR_TCIE;
	NVIC_SetPriority(DMA1_Channel1_IRQn, 5);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}


//init_chanel DMA for USART
void dma_usart2_tx(uint32_t *array, uint8_t size){
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel4->CPAR = (uint32_t)(&(USART2->TDR));
	DMA1_Channel4->CMAR = (uint32_t)(array);
	DMA1_Channel4->CNDTR = size;
	DMA1_Channel4->CCR |= DMA_CCR_PL_1;
	DMA1_Channel4->CCR |= DMA_CCR_PSIZE_1;
	DMA1_Channel4->CCR |= DMA_CCR_MSIZE_1; //32bit
	DMA1_Channel4->CCR |= DMA_CCR_MINC;
	DMA1_Channel4->CCR |= DMA_CCR_DIR;
}
