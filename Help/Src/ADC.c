/*
 * ADC.c
 *
 *  Created on: Oct 16, 2021
 *      Author: Владимир
 */


#include "ADC.h"

uint16_t data_adc_DMA[Size_adc];

// timer settings 15 for a period of 1 microsecond
void TIM15_init_TRG0() {
	TIM15->CR1 |= TIM_CR1_ARPE;
	RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
	TIM15->ARR = 480-1;
	TIM15->PSC = 10-1;
	TIM15->CR2 |= TIM_CR2_MMS_1;  //resolution TRGO
	TIM15->CR1 |= TIM_CR1_CEN;
}

void ADC_config(){
	GPIO_config();
	TIM15_init_TRG0();
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->CR2 |= RCC_CR2_HSI14ON;  					//init 14 Mhz
	while ((RCC->CR2 & RCC_CR2_HSI14RDY) != RCC_CR2_HSI14RDY)
	ADC1->SMPR |= ADC_SMPR_SMP_2 | ADC_SMPR_SMP_1; 	// 71.5 ADC clock cycles
	ADC1->CFGR1 |= ADC_CFGR1_CONT;					//continuous conversion
	ADC1->CHSELR = ADC_CHSELR_CHSEL10;				//10 entrance
	ADC1->CFGR1|=ADC_CFGR1_EXTEN_0;
	ADC1->CFGR1 |= ADC_CFGR1_EXTSEL_2;
	ADC1->CFGR1 &=~ADC_CFGR1_DISCEN;
	ADC1->CFGR1 |= ADC_CFGR1_DMACFG;
	ADC1->CFGR1 |= ADC_CFGR1_DMAEN;					//enabling DMA transmission
	dma_adc(&data_adc_DMA[0],Size_adc);
	ADC1->CR |= ADC_CR_ADEN;						//enabling the ADC
	ADC1->CR |= ADC_CR_ADSTART;						//start of conversion
}

void start_convert(){

	DMA1_Channel1->CCR &= ~DMA_CCR_EN;	//off DMA channel
	DMA1_Channel1->CMAR = (uint32_t)(data_adc_DMA);
	DMA1_Channel1->CNDTR = Size_adc;
	DMA1_Channel1->CCR |= DMA_CCR_EN;	//on DMA channel
	ADC1->CR |= ADC_CR_ADEN; 			//enabling the ADC
	ADC1->CR |= ADC_CR_ADSTART;			//start of conversion
}


uint16_t ADC_SR(){
	uint32_t sum=0;
	for (int i=0; i<Size_adc; i++){
		sum+=data_adc_DMA[i];
	}
	sum=sum/Size_adc;	//finding the average value

	return sum;
}


