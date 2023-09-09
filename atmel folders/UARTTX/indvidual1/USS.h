/*
 * USS.h
 *
 * Created: 9/9/2023 12:30:28 AM
 *  Author: Masha
 */ 


#ifndef USS_H_
#define USS_H_

#include <avr/io.h>

#define USS_PORT         PORTC
#define USS_PIN          PINC
#define USS_DDR          DDRC
#define USS_TRIGGER_PIN  PC0
#define USS_ECHO_PIN     PC1

#define USS_ERROR        -1
#define USS_NO_OBSTACLE  -2

void USS_Init();
void USS_Trigger();
uint16_t USS_GetPulseWidth();



#endif /* USS_H_ */