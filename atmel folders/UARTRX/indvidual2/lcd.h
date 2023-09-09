#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8000000UL
#include "stdio.h"
#include <avr/io.h>
#include <util/delay.h>


#define LCD_PORT               PORTA
#define DataDir_LCD_PORT       DDRA
#define LCD_CONTROL_PORT       PORTB
#define DataDir_LCD_CONTROL    DDRB
#define EN_SWITCH              6
#define RW_SWITCH              5
#define RS_SWITCH              4
#define DATA_SHIFT             0  // Set to 4 for 4-bit mode

// Choose whether to operate in 4 or 8 bit mode
#define EIGHT_BIT_MODE
//#define FOUR_BIT_MODE

// Hexadecimal instructions to be written to the instruction register
#define LCD_FUNCTION_8BIT_2LINES     (0x38)
#define LCD_FUNCTION_4BIT_2LINES     (0x28)
#define LCD_MOVE_DISP_RIGHT          (0x1C)
#define LCD_MOVE_DISP_LEFT           (0x18)
#define LCD_MOVE_CURSOR_RIGHT        (0x14)
#define LCD_MOVE_CURSOR_LEFT         (0x10)
#define LCD_DISP_OFF                 (0x08)
#define LCD_DISP_ON_CURSOR           (0x0E)
#define LCD_DISP_ON_CURSOR_BLINK     (0x0F)
#define LCD_DISP_ON_BLINK            (0x0D)
#define LCD_DISP_ON                  (0x0C)
#define LCD_ENTRY_DEC                (0x04)
#define LCD_ENTRY_DEC_SHIFT          (0x05)
#define LCD_ENTRY_INC                (0x06)
#define LCD_ENTRY_INC_SHIFT          (0x07)
#define LCD_BEGIN_AT_FIRST_ROW       (0x80)
#define LCD_BEGIN_AT_SECOND_ROW      (0xC0)
#define LCD_CLEAR                    (0x01)
#define LCD_ENTRY_MODE               (0x06)

// Prototypes
void LCD_Init(void);
void LCD_Clear_Screen(void);
void LCD_Send_Command(unsigned char command);
void LCD_Send_Character(unsigned char character);
void LCD_Send_String(char *string);
void LCD_Kick(void);
void LCD_Check_Is_Busy(void);
void LCD_gotoXY(unsigned char line, unsigned char position);
void LCD_Display_Number(int Number);
void LCD_Display_Real_Number(double Number);

#endif /* LCD_H_ */
