/*
 * pwmdac.c
 *
 * Created: 14.10.2020 14:51:45
 *  Author: EAG
 */
#ifndef PWMDAC_H_
#define PWMDAC_H_

inline void SetV(float U)
{
#ifdef pwmdac10b
//step 19.53mV
	#define WU0 0
	#define WU1 1
	#define WU2 1
	#define WU3 1
	if (U > 10.0){U = 10.0;}
	if (U < -10.0){U = -10.0;}
	uint16_t D = (uint16_t)(1023.0f * (U+10.0f) / 20.0f);
	ICR1 = 1023;
	OCR1A = D;
	OCR1B = D;
	OCR1C = D;
	TCCR1A = (2 << COM1A0) | (3 << COM1B0) | (1 << COM1C0) | (WU1 << WGM11) | (WU0 << WGM10);	// set fast PWM Mode
	TCCR1B = (0 << ICNC1) | (0 << ICES1) | (WU3 << WGM13) | (WU2 << WGM12) | (1 << CS10);	// set prescaler to 8 and starts PWM
	TCCR1C = (0 << FOC1A) | (0 << FOC1B) | (0 << FOC1C);
#else
#ifdef pwmdac9b
//step 39.06mV
	#define WU0 0
	#define WU1 1
	#define WU2 0
	#define WU3 0
	if (U > 10.0){U = 10.0;}
	if (U < -10.0){U = -10.0;}
	uint16_t D = (uint16_t)(511.0f * (U+10.0f) / 20.0f);
	ICR1 = 511;
	OCR1A = D;
	OCR1B = D;
	OCR1C = D;
	TCCR1A = (2 << COM1A0) | (3 << COM1B0) | (1 << COM1C0) | (WU1 << WGM11) | (WU0 << WGM10);	// set fast PWM Mode
	TCCR1B = (0 << ICNC1) | (0 << ICES1) | (WU3 << WGM13) | (WU2 << WGM12) | (1 << CS10);	// set prescaler to 8 and starts PWM
	TCCR1C = (0 << FOC1A) | (0 << FOC1B) | (0 << FOC1C);
#else
#ifdef pwmdac8b
//step 78.43mV
	#define WU0 1
	#define WU1 0
	#define WU2 0
	#define WU3 0
	if (U > 10.0){U = 10.0;}
	if (U < -10.0){U = -10.0;}
	uint8_t D = (uint8_t)(255.0f * (U+10.0f) / 20.0f);
	ICR1 = 255;
	OCR1A = D;
	OCR1B = D;
	OCR1C = D;
	TCCR1A = (2 << COM1A0) | (3 << COM1B0) | (1 << COM1C0) | (WU1 << WGM11) | (WU0 << WGM10);	// set fast PWM Mode
	TCCR1B = (0 << ICNC1) | (0 << ICES1) | (WU3 << WGM13) | (WU2 << WGM12) | (1 << CS10);	// set prescaler to 8 and starts PWM
	TCCR1C = (0 << FOC1A) | (0 << FOC1B) | (0 << FOC1C);
#else
	#error "pwm dac not defined resolution!"
#endif // pwmdac8b
#endif // pwmdac9b
#endif // pwmdac10b
}

#endif /* PWMDAC_H_ */
