/*
 * one_wire_ds18b20.h
 *
 *  Created on: 13 нояб. 2021 г.
 *      Author: Владимир
 */

#ifndef ONE_WIRE_DS18B20_H_
#define ONE_WIRE_DS18B20_H_

#include "stm32f0xx.h"
#include "GPIO_lib.h"
#include "us_delay_funck.h"

#define	DS18B20_RES_9	0x1F		//93,75 ms (sensor accuracy 0.5C) it is necessary to initialize
#define	DS18B20_RES_10	0x3F		//187.5 ms (sensor accuracy 0.25C) it is necessary to initialize
#define	DS18B20_RES_11	0x5F 		//375 ms (sensor accuracy 0.125C)  it is necessary to initialize
#define	DS18B20_RES_12	0x7F 		//750 ms (sensor accuracy 0.0625C) by default
#define	DS18B20_ERR_OK	1			//the sensor is working properly
#define	DS18B20_ERR_NO_SENSOR	0	//the sensor is not responding
#define SET_OUT()	(CurrGPIO->MODER |= 1 << curr_pin * 2)
#define OUT_1()	(CurrGPIO->BSRR = 1 << curr_pin) 			//High lever signal
#define OUT_0()	(CurrGPIO->BSRR = 1 << (curr_pin + 16)) 	//low lever signal
#define SET_IN()	(CurrGPIO->MODER &= ~(1 << curr_pin*2))


void ds18b20_Init(GPIO_TypeDef *GPIO, uint16_t num_pin);
uint32_t ds18b20_GetTemperature();
void ds18b20_StartMeas();
void ds18b20_SkipRom();
uint8_t ds18b20_isConversion();

#endif /* ONE_WIRE_DS18B20_H_ */
