/*
 * USS.c
 *
 * Created: 9/9/2023 12:30:40 AM
 *  Author: Masha
 */ 

#define F_CPU 16000000UL
#include "USS.h"
#include <util/delay.h>

void USS_Init() {
	USS_DDR |= (1 << USS_TRIGGER_PIN); // Set trigger pin as output
}

void USS_Trigger() {
	// Generate a 10uS pulse on the trigger line
	USS_PORT |= (1 << USS_TRIGGER_PIN); // High
	_delay_us(10);                     // Wait for 10uS
	USS_PORT &= ~(1 << USS_TRIGGER_PIN);// Low
}

uint16_t USS_GetPulseWidth() {
	uint32_t i, result;

	// Check if the ultrasonic sensor is working or connected properly
	for (i = 0; i < 600000; i++) {
		if (!(USS_PIN & (1 << USS_ECHO_PIN)))
		continue; // Line is still low, so wait
		else
		break; // High edge detected, so break
	}

	if (i == 600000)
	return USS_ERROR; // Timeout

	// High Edge Found

	// Setup Timer1
	TCCR1A = 0X00;
	TCCR1B = (1 << CS11); // Set timer resolution
	TCNT1 = 0x00;         // Start the counter

	// Check if there is any object
	for (i = 0; i < 600000; i++) {
		if (USS_PIN & (1 << USS_ECHO_PIN)) {
			if (TCNT1 > 60000)
			break;
			else
			continue;
		} else
		break;
	}

	if (i == 600000)
	return USS_NO_OBSTACLE; // Timeout

	// Falling edge found

	result = TCNT1;

	// Stop Timer
	TCCR1B = 0x00;

	if (result > 60000)
	return USS_NO_OBSTACLE;
	else
	return (result >> 1);
}
