/*
 * one_wire_ds18b20.c
 *
 *  Created on: 13 нояб. 2021 г.
 *      Author: Владимир
 */

#include "one_wire_ds18b20.h"

GPIO_TypeDef *CurrGPIO;
uint16_t curr_pin;


static uint8_t reset_ds18() {
	SET_OUT();	//data recording
	OUT_0();
	us_delay(510);
	SET_IN();	//reading data
	us_delay(88);
	if ((CurrGPIO->IDR & (1 << curr_pin))) {
		SET_OUT();
		OUT_1();
		GPIOC->BSRR = GPIO_BSRR_BR_8; //LED off
		return DS18B20_ERR_NO_SENSOR; //error no init_sesor
	}
	GPIOC->BSRR = GPIO_BSRR_BS_8; //LED on
	us_delay(300);

	SET_IN();
	return DS18B20_ERR_OK;
}

//recording commands to the sensor
static void write_ds18(uint32_t data, uint8_t num_bit) {
	SET_OUT();

	for (uint8_t i = 0; i < num_bit; i++)
	{
		OUT_0();
		us_delay(1);

		if ((data & (1 << i))) {
			OUT_1();
		}
		us_delay(88);

		OUT_1();
		us_delay(2);
	}
	SET_IN();
}

//reading data received from the sensor
static uint32_t read_ds18(uint8_t count_bit) {
	uint32_t data = 0;
	for (uint8_t i = 0; i < count_bit; i++) {
		SET_OUT();
		OUT_0();
		us_delay(4);
		SET_IN();
		us_delay(4);
		data |= ((CurrGPIO->IDR & (1 << curr_pin)) >> curr_pin) << i;
		us_delay(45);
	}

	SET_IN();
	return data;
}


void ds18b20_Init(GPIO_TypeDef *GPIO, uint16_t num_pin) {
	InitGPIO_led();
	InitGPIO_RCC(GPIO);
	CurrGPIO = GPIO;
	curr_pin = num_pin;

	SET_OUT();
	reset_ds18();
	ds18b20_SkipRom();
}


uint32_t ds18b20_GetTemperature(){
	uint32_t temperature = 0;
	reset_ds18();
	ds18b20_SkipRom();
	us_delay(10);				//10uS
	write_ds18(0xBE, 8);			//read scratchpad
	us_delay(2);				//2uS
	temperature = read_ds18(16);	//read data from device
	return temperature;
}

void ds18b20_StartMeas() {
	reset_ds18();
	ds18b20_SkipRom();
	us_delay(10);				//10 uS
	write_ds18(0x44, 8);			//convert_T init single temperature conversion
}


void ds18b20_SkipRom() {
	write_ds18(0xCC, 8); 			//skip_ROM ds18b20
}

uint8_t ds18b20_isConversion() {
	SET_IN();
	us_delay(30);
	if (CurrGPIO->IDR & (1 << curr_pin)) {
		return 1;	//conversion is done
	}

	return 0; //conversion is default
}
