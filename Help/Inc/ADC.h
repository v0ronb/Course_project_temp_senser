/*
 * ADC.h
 *
 *  Created on: Oct 16, 2021
 *      Author: Владимир
 */

#ifndef SRC_ADC_H_
#define SRC_ADC_H_

#include "stm32f0xx.h"
#include "dma.h"
#include "GPIO_lib.h"

#define Size_adc 64

void ADC_config();
void TIM15_init_TRG0();
void start_convert();
uint16_t ADC_SR();

#endif /* SRC_ADC_H_ */
