/*
 * adc.h
 *
 * Created: 14.10.2020 15:07:04
 *  Author: EAG
 */ 


#ifndef ADC_H_
#define ADC_H_

#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void SetVREF256()
{
	ADMUX = (3 << REFS0);	//AVCC with external capacitor at AREF pin
	_delay_ms(500);
}

void SetVREF5()
{
	ADMUX = (1 << REFS0);	//AVCC with external capacitor at AREF pin
	_delay_ms(500);
}

uint16_t GetADC(uint8_t ch)
{
	SetVREF5();
	ADMUX = (1 << REFS0)|(ch&7);	//AVCC with external capacitor at AREF pin
	ADCSRA = (1 << ADEN)|(0 << ADFR)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);	//ADC Prescaler Select Bits
	ADCSRA |= (1 << ADSC);			//ADC Start Conversion
	while((ADCSRA&(1<<ADIF))==0);
	return ADC;
}

uint16_t GetADC256(uint8_t ch)
{
	SetVREF256();
	ADMUX = (3 << REFS0)|(ch&7);	//Internal 2.56V Voltage Reference with external capacitor at AREF pin
	ADCSRA = (1 << ADEN)|(0 << ADFR)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);	//ADC Prescaler Select Bits
	ADCSRA |= (1 << ADSC);			//ADC Start Conversion
	while((ADCSRA&(1<<ADIF))==0);
	return ADC;
}

float GetVADC0()
{
	return (float)GetADC(1) * 5.0 / 1023.0;
}

float GetVADC1()
{
	return (float)GetADC(1) * 20.0 / 1023.0 -10.0;
}

float GetR_A13()
{
	//	float Ur1 = 1.0;
	//	float R;// = Ur1 / ((5 - Ur1) / 1000.0); //R = Ur1 / I
	//	R = Ur1 * 1000.0f / (5.0f - Ur1);
	//	R = 1023 * x / (1023 - 1023)
	//0.0049 = 0,978
	//0,0098 = 1,959
	//0.5V = 222,22
	//1V = 250
	//2V =	333,333
	//4.995 = 1022000
	float D = (float)GetADC(5) * 5.0f / 1023.0f;
	return D * 1000.0f / (5.0f - D);
}

float GetR_A14()
{
	float D = (float)GetADC(6) * 5.0f / 1023.0f;
	return D * 1000.0f / (5.0f - D);
}

float GetR_B15()
{
	float D = (float)GetADC(7) * 5.0f / 1023.0f;
	return D * 1000.0f / (5.0f - D);
}

volatile float V5;
volatile float V15;
volatile float V15n;

void GetVSupply()
{
	V5 = (float)GetADC256(2) * 5.12f / 1023.0f;
	V15 = (float)GetADC256(4) * 15.616f / 1023.0f;
	float V = (float)GetADC256(3) * 2.56f / 1023.0f;
	V15n = (V - V5) * 6.1f + V5;
}

#endif /* ADC_H_ */