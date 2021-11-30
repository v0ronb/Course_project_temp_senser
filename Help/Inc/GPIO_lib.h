/*
 * GPIO_lib.h
 *
 *  Created on: 13 нояб. 2021 г.
 *      Author: Владимир
 */

#ifndef GPIO_LIB_H_
#define GPIO_LIB_H_

#include "stm32f0xx.h"

void GPIO_config();
void GPIO_DHT11_init();
void InitGPIO_RCC(GPIO_TypeDef *GPIO);
void InitGPIO_led();

#endif /* GPIO_LIB_H_ */
