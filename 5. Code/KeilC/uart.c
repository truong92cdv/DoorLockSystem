#include <uart.h>
#include <port.h>

void UART_init()
{
	TMOD &= 0x2F; 
	TMOD |= 0x20;           // 0010 xxxx - Timer1 hoat dong o che do 8bit tu dong nap lai
	TH1 = 0xFD;				// Toc do baud rate 9600
	SCON = 0x50;			// UART mode 1
	TR1 = 1;				// Timer1 bat dau chay
	TI = 1;					// San sang gui du lieu	
}

void UART_write_char(unsigned char c)
{
	while(TI == 0);
	TI = 0;
	SBUF = c;
}

void UART_write_string(unsigned char *s)
{
	while(*s)
		UART_write_char(*s++);
}	

char UART_data_ready() {
	return RI;
}

char UART_read()
{
	RI = 0;
	return SBUF;
}