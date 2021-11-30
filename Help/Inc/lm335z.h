/*
 * lm335z.h
 *
 *  Created on: 12 нояб. 2021 г.
 *      Author: Владимир
 */

#ifndef LM335Z_H_
#define LM335Z_H_

#include "stm32f0xx.h"
#include "math.h"
#include "ADC.h"
#include "usart.h"

#define MAX_ADC 3416 		//maximum ADC value for 100 degrees
#define MIN_ADC 2501 		//minimum ADC value for 0 degrees
#define MAX_volt 2.54 		//maximum volt value for 100 degrees
#define MIN_volt 1.86		//minimum volt value for 0 degrees
#define colvo_mV 13.44		//sampling step
#define coef_propor 1.47	//voltage divider division coefficient


void lm335z_init();
void lm335z_start_convert();
void get_volt(uint16_t volt);
void get_temp();

#endif /* LM335Z_H_ */
