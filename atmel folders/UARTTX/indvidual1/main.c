#define F_CPU 16000000UL // 16 MHz clock speed




#include <avr/io.h>             // This header file includes the appropriate Input/output definitions for the device
#include <util/delay.h>         // to use delay function we need to include this library
#include <stdlib.h>             // we'll be using itoa() function to convert integer to character array that resides in this library

#include "USS.h"
#include "lcd.h"
#include "uart.h"



int distance, previous_distance;


int main(void)
{
	UART_init(9600);
	LCD_Init();
    USS_Init();

	uint16_t r;
	
    while (1) 
    {
		//Send a trigger pulse
		USS_Trigger();               // calling the ultrasonic sound wave generator function

		//Measure the width of pulse
		r=USS_GetPulseWidth();             // getting the duration of the ultrasound took to echo back after hitting the object

		//Handle Errors
		if(r==USS_ERROR)                // if microcontroller doesn't get any pulse then it will set the US_ERROR variable to -1
		// the following code will check if there is error then it will be displayed on the LCD screen
		{
			
		}
		else
		{
			
			distance=(r*0.034/2.0);	// This will give the distance in centimeters
			LCD_gotoXY(0,0);
			LCD_Display_Number(distance);
			u8 dist[20];    // Create a character array to hold the string
			sprintf(dist, "%d", distance);
			UART_sendString(dist);
			
			
			
			previous_distance = distance;
			_delay_ms(30);
			
			
			
		}
    }
}

