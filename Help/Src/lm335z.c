/*
 * lm335z.c
 *
 *  Created on: 12 нояб. 2021 г.
 *      Author: Владимир
 */


#include "lm335z.h"

#define send

float VOLTAGE=0;
float TEMP=0;
uint16_t sr_data=0;


void lm335z_init(){
	ADC_config(); // ADC init
}

void lm335z_start_convert(){
	start_convert(); //Start work ADC
	sr_data = ADC_SR(); //send average
	get_volt(sr_data); // convertation to V
	get_temp(); // convertation to C
#ifdef send
	send_data(TEMP); // delivery data
#endif
}

void get_volt(uint16_t volt){

	VOLTAGE = ((volt-MIN_ADC)/colvo_mV)*0.01;
	VOLTAGE = (MIN_volt+VOLTAGE)*coef_propor;
}

void get_temp(){
	TEMP=(VOLTAGE/0.01)-273.15;
}

