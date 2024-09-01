#include <keypad.h>
#include <port.h>
#include <delay.h>
#include <lcd.h>

char getKeyPad()
{
    int x = 0;
    while (x == 0)
    {
        ROW1 = 0;
        ROW2 = 1;
        ROW3 = 1;
        ROW4 = 1;
        if (COL1 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '1';
        }
        if (COL2 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '2';
        }
        if (COL3 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '3';
        }
		if (COL4 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return 'A';
        }

        ROW1 = 1;
        ROW2 = 0;
        ROW3 = 1;
        ROW4 = 1;

        if (COL1 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '4';
        }
        if (COL2 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '5';
        }
        if (COL3 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '6';
        }
		if (COL4 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return 'B';
        }

        ROW1 = 1;
        ROW2 = 1;
        ROW3 = 0;
        ROW4 = 1;
        if (COL1 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '7';
        }
        if (COL2 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '8';
        }
        if (COL3 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '9';
        }
		if (COL4 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return 'C';
        }

        ROW1 = 1;
        ROW2 = 1;
        ROW3 = 1;
        ROW4 = 0;

        if (COL1 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '*';
        }
        if (COL2 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '0';
        }
        if (COL3 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return '#';
        }
		if (COL4 == 0)
        {
            LCD_char('*');
            delay_ms(100);
            x = 1;
            return 'D';
        }
    }
}