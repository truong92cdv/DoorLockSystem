#ifndef __I2C_H__
#define __I2C_H__

#include <reg52.h>
#include <port.h>

void I2C_start();
void I2C_stop();
unsigned char I2C_sendByte(unsigned char dat);
unsigned char I2C_readByte();
void EEPROM_write(unsigned char addr,unsigned char dat);
unsigned char EEPROM_read(unsigned char addr);

#endif