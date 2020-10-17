/*
 * stend0029.c
 *
 * Created: 09.10.2020 23:43:19
 * Author : EAG
 */ 
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#define pwmdac10b
#include "pwmdac.h"
#include "adc.h"

int main(void)
{
	DDRA = 0;
	DDRB = (1<<PB7)|(1<<PB6)|(1<<PB5);
	DDRC = 0;
	DDRD = 0;
	DDRE = 0;
	DDRF = 0;
	DDRG = (1<<PG0);
	SetV(0);
	init_uart(9600);
	
	float V1 = GetVADC1();
	float R5 = GetR_A13();
	
    while (1) 
    {
    }
}

