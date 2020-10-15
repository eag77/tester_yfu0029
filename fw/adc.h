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

float GetVADC1()
{
	return (float)GetADC(1) * 20.0 / 1023.0 -10.0;
}

float GetRADC5()
{
	return (float)GetADC(5) * 1 / 1023.0 -10.0;
}

#endif /* ADC_H_ */