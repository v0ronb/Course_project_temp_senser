/*
 * usart.h
 *
 *  Created on: 17 окт. 2021 г.
 *      Author: Владимир
 */

#ifndef SRC_USART_H_
#define SRC_USART_H_

#include "stm32f0xx.h"
#include "dma.h"

#define BAUD  38400

#define SIZE_TEMP 2

void usart_init();
void usart_gpio_init();
void send_data(float temperature);
void usart_start();

#endif /* SRC_USART_H_ */
