#ifndef __PORT_H__
#define __PORT_H__

#include <reg52.h>

#define LCD_DATA 	P0
#define KEYPAD 		P1

sbit ROW1 		= P1^7;
sbit ROW2 		= P1^6;
sbit ROW3 		= P1^5;
sbit ROW4 		= P1^4;
sbit COL1 		= P1^3;
sbit COL2 		= P1^2;
sbit COL3 		= P1^1;
sbit COL4 		= P1^0;

sbit LCD_EN 	= P2^7;
sbit LCD_RS 	= P2^6;
sbit LCD_RW 	= P2^5;

sbit SERVO_PIN 	= P2^4;
sbit IRIN 		= P3^2;

#endif