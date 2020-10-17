/*
 * adc.h
 *
 * Created: 14.10.2020 15:07:04
 *  Author: EAG
 */ 


#ifndef ADC_H_
#define ADC_H_

uint16_t GetADC(uint8_t ch)
{
	ADMUX = (1 << REFS0)|(ch&7);	//AVCC with external capacitor at AREF pin
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
	//0.125 = 205,128
	//0.25V = 210
	//0.5V = 222,22
	//1V = 250
	//1.5V = 285
	//2V =	333,333
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

#endif /* ADC_H_ */