/*
 * ds18b20.c
 *
 *  Created on: 13 нояб. 2021 г.
 *      Author: Vladimir Lyalin
 */

#include "ds18b20.h"

#define send

uint32_t array_temp[2];
float real_temp = 0;
uint32_t temperature = 0;



// conversion to true temperature
void conversion_to_real(){
	temperature = ds18b20_GetTemperature();
	real_temp = (temperature & 0xFFF) * 0.0625;
}

//delivery data
void sending_data_ds18b20(){
	ds18b20_StartMeas();
	us_delay(800000); //752 ms sensor polling for 12 bit resolution
	conversion_to_real();
#ifdef send
	send_data(real_temp);
#endif
}

//tack port
void ds18b20_Init_Work(){
	ds18b20_Init(GPIO, PORT);
}
