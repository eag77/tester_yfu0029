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

#define EN_SET_L (PORTG |= 1)
#define EN_SET_H (PORTG &= 0xFE)

#define Q1_State ((PINC & (1<<PC4)) != 0)
#define Q2_State ((PINC & (1<<PC7)) != 0)
#define Q3_State ((PINC & (1<<PC6)) != 0)
#define QE1_State ((PINC & (1<<PC3)) != 0)
#define QE2_State ((PINC & (1<<PC5)) != 0)
#define QE3_State ((PINC & (1<<PC1)) != 0)
#define QUIT_State ((PINC & (1<<PC0)) != 0)
#define QUITN_State ((PINC & (1<<PC2)) != 0)
#define QNOT_State ((PINA & (1<<PA0)) != 0)
#define EN_State ((PIND & (1<<PD7)) != 0)
#define Q123_State ((Q1_State ? 1:0) | (Q2_State ? 2:0) | (Q3_State ? 4:0))
#define QE123_State ((QE1_State ? 1:0) | (QE2_State ? 2:0) | (QE3_State ? 4:0))

#define RES_TEST_L	1
#define RES_TEST_H	2
#define RES_ERROR_L	4
#define RES_ERROR_H	8

uint8_t RESULT_Q1;
uint8_t RESULT_Q2;
uint8_t RESULT_Q3;
uint8_t RESULT_QE1;
uint8_t RESULT_QE2;
uint8_t RESULT_QE3;
uint8_t RESULT_QUIT;
uint8_t RESULT_QUITN;
uint8_t RESULT_QNOT;

void TestQUIT()
{
	
}

void Test(uint8_t Vin, uint8_t Vout, uint8_t* Res)
{
	if((*Res & (RES_TEST_H | RES_TEST_L)) == (RES_TEST_H | RES_TEST_L))
	return;

	if(Vin != 0)
	{
		if (Vout != 0)
		{
			*Res |=	RES_TEST_L | RES_ERROR_L;
		}
		else
		{
			*Res |=	RES_TEST_L;
		}
	}
	else
	{
		if (Vout != 0)
		{
			*Res |=	RES_TEST_H;
		}
		else
		{
			*Res |=	RES_TEST_H | RES_ERROR_H;
		}
	}
}

void TestQUITN(uint8_t Vin, uint8_t Vout, uint8_t Res)
{
	if((RESULT_QUITN & (RES_TEST_H | RES_TEST_L)) == (RES_TEST_H | RES_TEST_L))
	return;

	if(QUIT_State != 0)
	{
		if (QUITN_State != 0)
		{
			RESULT_QUITN |=	RES_TEST_L | RES_ERROR_L;
		}
		else
		{
			RESULT_QUITN |=	RES_TEST_L;
		}
	}
	else
	{
		if (QUITN_State != 0)
		{
			RESULT_QUITN |=	RES_TEST_H;
		}
		else
		{
			RESULT_QUITN |=	RES_TEST_H | RES_ERROR_H;
		}
	}
}

int main(void)
{
	DDRA = 0;
	DDRB = (1<<PB7)|(1<<PB6)|(1<<PB5);
	DDRC = 0;
	DDRD = 0;
	DDRE = 0;
	DDRF = 0;
	DDRG = (1<<PG0);
	EN_SET_H;			//Все логические входы в "1"
	timer0_init();
	sei();
	SetV(0);
	uart_init(9600);
	printf("Тестер ЯФУ-0029\n");
//	printf("Tester YFU-0029\n");
//	_delay_ms(100);
	GetVSupply();
	printf("Питание:\n", V5);
	printf(" +5В: %fВ\n", V5);
	printf("+15В: %fВ\n", V15);
	printf("-15В: %fВ\n", V15n);
	
	if (V15n > 11.0f)
	{
		printf("Отрицательное напряжение питания %f меньше допустимого!\n", V15n);
	}

	if (V15 < 11.0f)
	{
		printf("Положительное напряжение питания %f меньше допустимого!\n", V15n);
	}

	if ((V5 < 4.95f)||(V5 > 5.05))
	{
		printf("5В напряжение: %f. Оно является опорным!\n", V15n);
	}
	
	if (!EN_State)
	{
		printf("Низкое напряжение логических входов!\n");
	}

	float RA14 = GetR_A14();	//
	float RB15 = GetR_B15();	//
	float RA13 = GetR_A13();	//

	if (RA14 < 100000.0)
	{
		printf("Сопротивление закрытого ключа D4 a10-a14 %f!\n", RA14);
	}

	if (RB15 < 100000.0)
	{
		printf("Сопротивление закрытого ключа D4 b10-b15 %f!\n", RB15);
	}

	if (RA13 < 100000.0)
	{
		printf("Сопротивление закрытого ключа D4 a11-a13 %f!\n", RA13);
	}

	if (QNOT_State)
	{
		printf("На выходе D1.1 высокий уровень!\n");
	}

	if (!QE1_State)
	{
		printf("На A20 низкий уровень!\n");
	}

	if (!QE2_State)
	{
		printf("На A18 низкий уровень!\n");
	}

	if (!QE3_State)
	{
		printf("На B20 низкий уровень!\n");
	}

	float V0 = GetVADC0();		//PWM 0..+5V
	float V1 = GetVADC1();		//IN -10..+10V
	
	uint8_t QS = Q123_State;
	uint8_t QES = QE123_State;
	
	if ((V0 < 2.48)||(V0 > 2.52))
	{
		printf("Напряжение ШИМ 2.5В: %0.3f! (Неисправность ШИМ тестера)\n", V0);
	}
	else
	{	
		if ((V1 < 0.05)&&(V1 > -0.05))
		{
			if ((QS & 1) != 0)
			{
				printf("На ИН1 высокий уровень!\n");
			}

			if ((QS & 2) != 0)
			{
				printf("На ИН2 высокий уровень!\n");
			}

			if ((QS & 4) != 0)
			{
				printf("На ИН3 высокий уровень!\n");
			}
		
			if (QS == 0)
			{
				if (QES == 7)
				{
					if(QUIT_State != 0)
					{
						printf("На \"Вых.пр.\" высокий уровень! Не испр. D3.1\n");
						if (QUITN_State == 0)
						{
							printf("На \"Вых.ин.\" низкий уровень! Не испр. D3.3\n");
						}
					}
					else
					{
						if (QUITN_State != 0)
						{
							printf("На \"Вых.ин.\" высокий уровень! Не испр. D3.3\n");
						}
					}
				}
				else
				{
				
				}
			
				printf("На ИН1 высокий уровень!\n");
			}
		}
		else
		{//Uin != 0V
			printf("Напряжение на входе не равно нулю! (Неисправность ЦАП тестера)\n");
		}
	}

	printf("Тест окончен!\n");
	
    while (1) 
    {
    }
}

