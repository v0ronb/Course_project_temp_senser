/*
 * one_wire_DHT.h
 *
 *  Created on: 13 нояб. 2021 г.
 *      Author: Владимир
 */

#ifndef ONE_WIRE_DHT_H_
#define ONE_WIRE_DHT_H_

#include "stm32f0xx.h"
#include "GPIO_lib.h"
#include "us_delay_funck.h"

#define GPIO_output() GPIOB->MODER|=GPIO_MODER_MODER13_0 	//setting up the output
#define GPIO_input() GPIOB->MODER&=~GPIO_MODER_MODER13		//setting up input
#define DHT11_Higt_port() GPIOB->ODR|=GPIO_ODR_13			//pulling the tire to the voltage
#define DHT11_Low_Port() GPIOB->ODR&=~GPIO_ODR_13			//pulling the tire to the ground


uint8_t dht11_GetData(uint8_t *data);


#endif /* ONE_WIRE_DHT_H_ */
