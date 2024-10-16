#ifndef __UART_H__
#define __UART_H__

#include <reg52.h>

void UART_init();
void UART_write_char(unsigned char c);
void UART_write_string(unsigned char *s);
char UART_data_ready();
char UART_read();

#endif