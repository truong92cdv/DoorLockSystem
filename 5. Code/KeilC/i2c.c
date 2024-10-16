#include <i2c.h>
#include <port.h>

void Delay10us()
{
	unsigned char a,b;
	for(b=1;b>0;b--)
		for(a=2;a>0;a--);

}

void I2C_start()
{
	SDA=1;
	Delay10us();
	SCL=1;
	Delay10us();
	SDA=0;
	Delay10us();
	SCL=0;			
	Delay10us();		
}

void I2C_stop()
{
	SDA=0;
	Delay10us();
	SCL=1;
	Delay10us();
	SDA=1;
	Delay10us();		
}

unsigned char I2C_sendByte(unsigned char dat)
{
	unsigned char a=0,b=0;	
	for(a=0;a<8;a++)
	{
		SDA=dat>>7;
		dat=dat<<1;
		Delay10us();
		SCL=1;
		Delay10us();
		SCL=0;
		Delay10us();		
	}
	SDA=1;
	Delay10us();
	SCL=1;
	while(SDA)
	{
		b++;
		if(b>200)
		{
			SCL=0;
			Delay10us();
			return 0;
		}
	}
	SCL=0;
	Delay10us();
 	return 1;		
}

unsigned char I2C_readByte()
{
	unsigned char a=0,dat=0;
	SDA=1;
	Delay10us();
	for(a=0;a<8;a++)
	{
		SCL=1;
		Delay10us();
		dat<<=1;
		dat|=SDA;
		Delay10us();
		SCL=0;
		Delay10us();
	}
	return dat;		
}

void EEPROM_write(unsigned char addr,unsigned char dat)
{
	I2C_start();
	I2C_sendByte(0xa0);
	I2C_sendByte(addr);
	I2C_sendByte(dat);
	I2C_stop();
}

unsigned char EEPROM_read(unsigned char addr)
{
	unsigned char num;
	I2C_start();
	I2C_sendByte(0xa0); 
	I2C_sendByte(addr); 
	I2C_start();
	I2C_sendByte(0xa1); 
	num = I2C_readByte(); 
	I2C_stop();
	return num;	
}