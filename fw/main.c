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
#include "uart.h"
#include "ClockT0.h"

int main(void)
{
	DDRA = 0;
	DDRB = (1<<PB7)|(1<<PB6)|(1<<PB5);
	DDRC = 0;
	DDRD = 0;
	DDRE = 0;
	DDRF = 0;
	DDRG = (1<<PG0);
	timer0_init();
	sei();
	SetV(0);
	uart_init(9600);
//	printf("Тестер ЯФУ-0029\n");
	printf("Tester YFU-0029\n");
	printf("%s\n",GetTime());
	float V0 = GetVADC0();		//PWM 0..+5V
	printf("%s\n",GetTime());
	float V1 = GetVADC1();		//IN -10..+10V
	printf("%s\n",GetTime());
	float RA13 = GetR_A13();	//
	printf("%s\n",GetTime());
	_delay_ms(500);
	printf("%s\n",GetTime());
	_delay_ms(500);
	printf("%s\n",GetTime());
	_delay_ms(500);
	printf("%s\n",GetTime());
	_delay_ms(500);
	
    while (1) 
    {
    }
}

