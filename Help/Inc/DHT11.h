/*
 * DHT11.h
 *
 *  Created on: 13 нояб. 2021 г.
 *      Author: Владимир
 */

#ifndef DHT11_H_
#define DHT11_H_

#include "stm32f0xx.h"
#include "usart.h"
#include "one_wire_DHT.h"

uint8_t DHT11_real_values();
void dht11_init();

#endif /* DHT11_H_ */
