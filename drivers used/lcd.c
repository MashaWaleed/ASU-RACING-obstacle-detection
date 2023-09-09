#include "lcd.h"

void LCD_Init(void)
{
	_delay_ms(20);
	DataDir_LCD_CONTROL |= (1 << EN_SWITCH | 1 << RW_SWITCH | 1 << RS_SWITCH); // Control port output
	LCD_CONTROL_PORT &= ~(1 << EN_SWITCH | 1 << RW_SWITCH | 1 << RS_SWITCH); // Clear all instruction bits for initialization phase

	DataDir_LCD_PORT = 0xFF; // Output

	_delay_ms(15);
	LCD_Clear_Screen();

	#ifdef EIGHT_BIT_MODE
	LCD_Send_Command(LCD_FUNCTION_8BIT_2LINES);
	#endif

	#ifdef FOUR_BIT_MODE
	LCD_Send_Command(0x02);
	LCD_Send_Command(LCD_FUNCTION_4BIT_2LINES);
	#endif

	LCD_Send_Command(LCD_ENTRY_MODE);
	LCD_Send_Command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_Send_Command(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_Clear_Screen(void)
{
	LCD_Send_Command(LCD_CLEAR);
}

void LCD_Send_Command(uint8_t command)
{
	#ifdef EIGHT_BIT_MODE
	LCD_Check_Is_Busy();

	LCD_PORT = command;
	LCD_CONTROL_PORT &= ~((1 << RW_SWITCH) | (1 << RS_SWITCH));
	LCD_Kick();
	#endif

	#ifdef FOUR_BIT_MODE
	LCD_Check_Is_Busy();
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	LCD_CONTROL_PORT &= ~((1 << RW_SWITCH) | (1 << RS_SWITCH));
	LCD_Kick();

	LCD_Check_Is_Busy();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	LCD_CONTROL_PORT &= ~((1 << RW_SWITCH) | (1 << RS_SWITCH));
	LCD_Kick();
	#endif
}

void LCD_Send_Character(uint8_t character)
{
	#ifdef EIGHT_BIT_MODE
	//LCD_Check_Is_Busy();
	LCD_CONTROL_PORT |= (1 << RS_SWITCH); // 1: Data Register
	LCD_PORT = (character << DATA_SHIFT);
	LCD_CONTROL_PORT |= (1 << RS_SWITCH); // 1: Data Register
	LCD_CONTROL_PORT &= ~(1 << RW_SWITCH); // 0: Write
	LCD_Kick();
	#endif

	#ifdef FOUR_BIT_MODE
	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
	LCD_CONTROL_PORT |= (1 << RS_SWITCH); // 1: Data Register
	LCD_CONTROL_PORT &= ~(1 << RW_SWITCH); // 0: Write
	LCD_Kick();

	LCD_Check_Is_Busy();
	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
	LCD_CONTROL_PORT |= (1 << RS_SWITCH); // 1: Data Register
	LCD_CONTROL_PORT &= ~(1 << RW_SWITCH); // 0: Write
	LCD_Kick();
	#endif
}

void LCD_Send_String(char *string)
{
	int count = 0;
	while (*string > 0)
	{
		count++;
		LCD_Send_Character(*string++);
		if (count == 16)
		{
			LCD_gotoXY(1, 0);
		}
		else if (count >= 32)
		{
			LCD_Clear_Screen();
			LCD_gotoXY(0, 0);
			count = 0;
		}
	}
}

void LCD_Kick(void)
{
	LCD_CONTROL_PORT &= ~(1 << EN_SWITCH);
	_delay_ms(50);
	LCD_CONTROL_PORT |= (1 << EN_SWITCH);
}

void LCD_Check_Is_Busy(void)
{
	DataDir_LCD_PORT &= ~(0xFF << DATA_SHIFT);
	LCD_CONTROL_PORT |= (1 << RW_SWITCH); // 1: Read
	LCD_CONTROL_PORT &= ~(1 << RS_SWITCH); // 0: Command Register

	LCD_Kick();

	DataDir_LCD_PORT = 0xFF;
	LCD_CONTROL_PORT &= ~(1 << RW_SWITCH); // 0: Write
}

void LCD_gotoXY(uint8_t line, uint8_t position)
{
	if (line == 0) // line 1
	{
		if (position < 16 && position >= 0)
		LCD_Send_Command(0x80 + position);
	}
	if (line == 1) //  line 2
	{
		if (position < 16 && position >= 0)
		LCD_Send_Command(0xC0 + position);
	}
}

void LCD_Display_Number(int Number)
{
	char str[7];
	sprintf(str, "%d", Number);

	LCD_Send_String(str);
}

void LCD_Display_Real_Number(double Number)
{
	char str[16];

	char *tmpsign = (Number < 0) ? "-" : "";
	float tmpVal = (Number < 0) ? -Number : Number;

	int tmpInt1 = tmpVal; // Get the integer value
	double tmpFraction = tmpVal - tmpInt1; // Get fraction value
	int tmpInt2 = tmpFraction * 10000; // Turn into integer

	sprintf(str, "%s%d.%05d", tmpsign, tmpInt1, tmpInt2);
	LCD_Send_String(str);
}
