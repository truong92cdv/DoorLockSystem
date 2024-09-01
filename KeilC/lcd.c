#include <lcd.h>
#include <port.h>
#include <delay.h>

void delay_ms(unsigned int t) {
    unsigned int i, j;
    for (i = 0; i < t; i++)
        for (j = 0; j < 112; j++);
}

void LCD_init()
{
	LCD_cmd(0x0F);
    LCD_cmd(0x38); 
    LCD_cmd(0x01); 
}

void LCD_cmd(unsigned char a)
{
    LCD_DATA=a;
    LCD_RS=0;
    LCD_RW=0;
    LCD_EN=1;
	delay_ms(1);
    LCD_EN=0;
	delay_ms(5);
}

void LCD_char(unsigned char b)
{
    LCD_DATA=b;
    LCD_RS=1;
    LCD_RW=0;
    LCD_EN=1;
    delay_ms(1);
    LCD_EN=0;
	delay_ms(5);
}

void LCD_string(unsigned char *s)
{
    while(*s) {
        LCD_char(*s++);
		delay_ms(50);
    }
}

void LCD_string_xy(unsigned char *s, char row, char pos)
{
	if (row == 1)
		LCD_cmd((pos & 0x0F)|0x80);
	else if (row == 2)
		LCD_cmd((pos & 0x0F)|0xC0);
	LCD_string(s);
}