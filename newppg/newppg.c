#define F_CPU 8000000UL
#include <stdio.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "USART_128.h"
#include "avr/iom128.h"
#define TH 120
uint8_t rate = 0;

void adc_init()
{
	ADMUX |=(1<<REFS0); //SETTING REFERENCE voltage to 5v
	ADCSRA |=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t readAdc()
{
	uint8_t ch = 0b00000000;
	ch &= 0b00000111;
	ADMUX |= ch;
	ADCSRA |=(1<<ADSC);
	while((ADCSRA & (1<<ADIF)));
	ADCSRA |=(1<<ADIF)|(1<<CS10)|(1<<CS12);
	//USART_TransmitNumber(1,0);
	return (ADC);
}
void freq_chk_init()
{
	
	
	//DDRA = 0b00000001;
	//TCCR1A |= ;
	TCCR1B |= (1<<WGM12)|(1<<CS12)|(1<<CS10);
	OCR1A = 15624;
	TIMSK |= (1<< OCIE1A);
	sei();
	//USART_Transmitchar('A',0);
	_delay_ms(100);
	
}
void frequency_chk(uint16_t var)
{
	if(var >= 400)
	{
		//USART_Transmitchar('a',0);
		rate++;
	}
	
}

uint8_t flag=0;


void main()
{
	uint16_t result;
	USART_Init(51,1);
	adc_init();
	freq_chk_init();
	
	while(1)
	{
		result = readAdc();
		_delay_ms(100);
		//USART_TransmitNumber(result,0);
		//frequency_chk(result);
		if(flag)
		{
			//if(result > 0)
			//{
				USART_TransmitString("ATD9834691317\r;",1);
				_delay_ms(3000);
			//}
			flag=0;
		}
		
	}
}



ISR(TIMER1_COMPA_vect)
{
	flag = 1;
}
