/*
 * us_delay_funck.c
 *
 *  Created on: 28 нояб. 2021 г.
 *      Author: Владимир
 */

#include "us_delay_funck.h"

//0.94 microsecond delay
void us_delay(uint32_t tick){
    tick*=(SystemCoreClock / 1000000)/9;
    while (tick--);
}
