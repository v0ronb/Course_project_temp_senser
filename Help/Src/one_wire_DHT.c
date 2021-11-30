/*
 * one_wire_DHT.c
 *
 *  Created on: 13 нояб. 2021 г.
 *      Author: Vladimir Lyalin RL6-79
 */


#include "one_wire_DHT.h"


uint8_t dht11_GetData(uint8_t *data){
	uint8_t i, j = 0;
	//reset port
	GPIO_output();
	DHT11_Higt_port();//High lever
	us_delay(10000); //10 ms delay
	DHT11_Low_Port();//low lever
	us_delay(21000);
	DHT11_Higt_port();//High lever
	GPIO_input();
	//wait sensor response
	us_delay(26);
	//while the sensor has not responded
	if(GPIOB->IDR & GPIO_IDR_13) {
		return 0;
	}
	us_delay(86);
	//until the sensor released the tire
	if(!(GPIOB->IDR & GPIO_IDR_13)) {
		return 0;
	}
	us_delay(86);

	for (j=0; j<5; j++)
	{
		data[j]=0;
		for(i=0; i<8; i++)
		{
			while(!(GPIOB->IDR & GPIO_IDR_13)); //waiting for release
			us_delay(34);
			if(GPIOB->IDR & GPIO_IDR_13) //if the tire has not been attracted to the ground during this time, then it means one, and if it has been attracted, then zero
				data[j] |= (1<<(7-i));
			while(GPIOB->IDR & GPIO_IDR_13); //waiting for the sensor to attract the tire (in the case of one)
		}
	}
	return 1;
}


