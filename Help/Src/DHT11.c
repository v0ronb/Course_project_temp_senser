/*
 * DHT11.c
 *
 *  Created on: 13 нояб. 2021 г.
 *      Author: Владимир
 */


#include "DHT11.h"

#define send

uint8_t data_dht11[5]={0,0,0,0,0};
float temp=0;
uint8_t humidity=0;

void dht11_init(){
	GPIO_DHT11_init();		//tack port
	DHT11_Higt_port();		//pulling the tire to the voltage
}

uint8_t DHT11_real_values(){
	if(dht11_GetData(data_dht11)){
		uint16_t  data_temp= data_dht11[2]*10+data_dht11[3];	//converting data to temperature
		temp = (float)data_temp/10;
		humidity = data_dht11[0];	//converting data to humidity
		us_delay(50);
	#ifdef send
	send_data(temp); // delivery data
	#endif
		return 1;
	}
	return 0;
}
