#include <reg52.h>
#include <port.h>
#include <delay.h>
#include <lcd.h>
#include <uart.h>
#include <servo.h>
#include <keypad.h>
#include <string.h>
#include <ir.h>
#include <i2c.h>
#include <stdio.h>

unsigned char pin[] = {"1234"};
unsigned char pinChange[] = {"*AB#"};
unsigned char pinCard[] = {"****"};
unsigned char Epin[4];

void check();

void main()
{
    unsigned int j;
	Servo_init();
	IR_init();
	LCD_init();
	UART_init();
	
	// read PIN from EEPROM
	for (j=0;j<4;j++)
	{
		pin[j] = EEPROM_read(j);
		delay_ms(1);
	}
		
    while (1)
    {
		unsigned int i = 0;
		LCD_cmd(0x01);
        LCD_string_xy("ENTER PIN NUMBER",0,0);
        delay_ms(100);
        LCD_cmd(0xc0); 
        while (pin[i] != '\0')
        {
            Epin[i] = getKeyPad();
            delay_ms(100);
            i++;
        }
        check();
    }
}

void check()
{
	unsigned char i, num;
	
	// Change PIN number
    if (Epin[0] == pinChange[0] && Epin[1] == pinChange[1] && Epin[2] == pinChange[2] && Epin[3] == pinChange[3] && Epin[4] == pinChange[4])
	{
		delay_ms(100);
		LCD_cmd(0x01);
        LCD_string_xy("ENTER NEW PIN",0,0);
        delay_ms(100);
        LCD_cmd(0xc0);
		i = 0;
        while (pin[i] != '\0')
        {
			num = getKeyIR();
			while(num==getKeyIR());
			num = getKeyIR();
			LCD_char(num);
			pin[i] = num;
			delay_ms(100);
			i++;
        }	
		// Save new pin to EEPROM
		for (i=0;i<4;i++)
		{
			EEPROM_write(i,pin[i]);
			delay_ms(1);
		}
		LCD_cmd(0x01);
		LCD_string_xy("PIN CHANGED!",0,0);
		delay_ms(500);
		LCD_cmd(0x01);
	}
	
	// Use CARD to signin
	else if (Epin[0] == pinCard[0] && Epin[1] == pinCard[1] && Epin[2] == pinCard[2] && Epin[3] == pinCard[3] && Epin[4] == pinCard[4])
	{
		LCD_cmd(0x01);
		LCD_string_xy("SWIPE YOUR CARD",0,0);
		delay_ms(100);
		num = _getkey();
		if (num == 1) {
			LCD_cmd(0x01);
			LCD_string_xy(" WELCOME!",0,0);			
			delay_ms(500);
			Servo_open();
			delay_ms(3000);
			Servo_close();
		} else {
			LCD_cmd(0x01);
			LCD_string_xy(" WRONG CARD!",0,0);
		}
	}
	
	// PIN correct
    else if (Epin[0] == pin[0] && Epin[1] == pin[1] && Epin[2] == pin[2] && Epin[3] == pin[3] && Epin[4] == pin[4])
    {
        LCD_cmd(0x01);
        LCD_string_xy(" WELCOME!",0,0);
        delay_ms(500);
		Servo_open();
        delay_ms(3000);
		Servo_close();
    }
	
	// wrong PIN
    else
    {
        LCD_cmd(0x01);
        LCD_string_xy("WRONG PIN",0,0);
        delay_ms(500);
        LCD_cmd(0x01);
    }
}