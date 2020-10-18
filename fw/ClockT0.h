/*
 * ClockT0.h
 *
 * Created: 18.10.2020 12:28:19
 *  Author: EAG
 */ 


#ifndef CLOCKT0_H_
#define CLOCKT0_H_

uint32_t ticks_t0;	//0.0001sec
char str[14] = {0};

char* GetTime()
{
	uint32_t C = ticks_t0;
	uint8_t H = (uint8_t)(C / (36000000));
	uint8_t M = (uint8_t)((C-(H*36000000))/(600000));
	uint8_t S = (uint8_t)((C-(H*36000000)-(M*600000))/10000);
	uint16_t mS = (C-(H*36000000)-(M*600000)-(S*10000));
	sprintf(str, "%02d:%02d:%02d.%04d", H, M, S, mS);
//	sprintf(str, "%02d:%02d:%02d.%04d", 1, 2, 3, 4);
	return str;
}

void timer0_init()
{//10kHz
	TIMSK = (0<<OCIE0)|(1<<TOIE0);
	OCR0 = 199;
	TCCR0 = (1<<WGM01)|(2<<CS00);	//CTC TOP OCR; clkT0S/8 (From prescaler)
}

ISR (TIMER0_OVF_vect)
{
	ticks_t0++;
}

ISR (TIMER0_COMP_vect)
{
}

#endif /* CLOCKT0_H_ */