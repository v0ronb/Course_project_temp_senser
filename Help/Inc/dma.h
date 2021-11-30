/*
 * dma.h
 *
 *  Created on: 12 нояб. 2021 г.
 *      Author: Владимир
 */

#ifndef DMA_H_
#define DMA_H_

#include "stm32f0xx.h"


void dma_adc(uint16_t *array_adc, uint8_t size);
void dma_usart2_tx(uint32_t *array, uint8_t size);

#endif /* DMA_H_ */
