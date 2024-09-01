#ifndef __LCD_H__
#define __LCD_H__

#include <reg52.h>

void delay_ms(unsigned int t);
void LCD_init();
void LCD_cmd(unsigned char a);
void LCD_char(unsigned char b);
void LCD_string(unsigned char *s);
void LCD_string_xy(unsigned char *s, char row, char pos);

#endif
