/*
 * ds18b20.h
 *
 *  Created on: 13 нояб. 2021 г.
 *      Author: Владимир
 */

#ifndef DS18B20_H_
#define DS18B20_H_

#include "stm32f0xx.h"
#include "one_wire_ds18b20.h"
#include "usart.h"

#define GPIO GPIOC
#define PORT 14


void conversion_to_real();
void ds18b20_Init_Work();
void sending_data_ds18b20();

#endif /* DS18B20_H_ */
