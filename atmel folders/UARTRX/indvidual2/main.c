/*
 * indvidual2.c
 *
 * Created: 9/9/2023 7:52:29 PM
 * Author : Masha
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include "avr/interrupt.h"
#include "util/delay.h"
#include "uart.h"
#include "lcd.h"


#define LED_PIN     (1 << PD2)
#define BUZZER_PIN  (1 << PD3)

volatile uint16_t buzzer_duration = 0;

void Timer0_Init() {
	TCCR0 = (1 << CS02) | (1 << CS00);
	TIMSK |= (1 << TOIE0);
	TCNT0 = 0;
}

void Timer1_Init() {
	TCCR1B = (1 << CS12) | (1 << CS10);
	TCNT1 = 0;
	TIMSK |= (1 << TOIE1);
}


void ToggleLED() {
	PORTD ^= LED_PIN;
}

void ControlBuzzer(uint16_t duration_ms) {
	buzzer_duration = duration_ms;
	PORTD |= BUZZER_PIN;
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

int main(void)
{
	DDRD |= (LED_PIN | BUZZER_PIN);
	Timer0_Init();
	Timer1_Init();
	
    UART_init(9600);
	sei();
	PORTD &= ~(1<<1);
    while (1) 
    {
		char str[20];
		int distance;
		UART_receiveString(str);
		if(sscanf(str, "%d", &distance) == 1)
		{
				if(distance <= 50)
				{
					ControlBuzzer(distance * 10);
					ToggleLED();
				}
				else{
					PORTD &= ~(1<<1);
					PORTD &= ~(1<<2);
				}
		}
    }
}
ISR(TIMER0_OVF_vect) {
	static uint16_t counter = 0;
	counter++;
	if (counter >= 250) {
		ToggleLED();
		counter = 0;
	}
}

ISR(TIMER1_OVF_vect) {
	if (buzzer_duration > 0) {
		buzzer_duration--;
		} else {
		PORTD &= ~BUZZER_PIN;
		TCCR1B = 0; 
	}
}
