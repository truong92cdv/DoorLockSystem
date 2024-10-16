#ifndef __IR_H__
#define __IR_H__

#include <reg52.h>
#include <port.h>
#include <lcd.h>

unsigned char IrValue[6];
unsigned char Time;

void DelayMs(unsigned int x); 	// Delay 0.14 ms
void IR_init();		
unsigned char getKeyIR();

void DelayMs(unsigned int x)
{
	unsigned char i;
	while(x--)
		for (i = 0; i<13; i++) {}
}

void IR_init()
{
	IT0=1;
	EX0=1;
	EA=1;
	IRIN=1;
}

void IR_read() interrupt 0
{
	unsigned char j,k;
	unsigned int err;
	Time=0;					 
	DelayMs(70);

	if(IRIN==0)
	{	 
		
		err=1000;	
		while((IRIN==0)&&(err>0))		
		{			
			DelayMs(1);
			err--;
		} 
		if(IRIN==1)		
		{
			err=500;
			while((IRIN==1)&&(err>0))	
			{
				DelayMs(1);
				err--;
			}
			for(k=0;k<4;k++)	
			{				
				for(j=0;j<8;j++)	
				{

					err=60;		
					while((IRIN==0)&&(err>0))
					{
						DelayMs(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))
					{
						DelayMs(1);
						Time++;
						err--;
						if(Time>30)
						{
							EX0=1;
							return;
						}
					}
					IrValue[k]>>=1;	
					if(Time>=8)	
					{
						IrValue[k]|=0x80;
					}
					Time=0;							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}			
}

unsigned char getKeyIR()
{
	unsigned char x,y,number;
	IrValue[4]=IrValue[2]>>4;	 	 	
	IrValue[5]=IrValue[2]&0x0f;			
	if(IrValue[4]>9)
	{	
		x = 0x37+IrValue[4];	
	}
	else
	{
		x = IrValue[4]+0x30;	
	}	
	if(IrValue[5]>9)
	{
		y = IrValue[5]+0x37;	
	}
	else
	{
		y = IrValue[5]+0x30;	
	}	
	if ((x=='E') && (y=='9')) number = '0';
	if ((x=='F') && (y=='3')) number = '1';
	if ((x=='E') && (y=='7')) number = '2';
	if ((x=='A') && (y=='1')) number = '3';
	if ((x=='F') && (y=='7')) number = '4';
	if ((x=='E') && (y=='3')) number = '5';
	if ((x=='A') && (y=='5')) number = '6';
	if ((x=='B') && (y=='D')) number = '7';
	if ((x=='A') && (y=='D')) number = '8';
	if ((x=='B') && (y=='5')) number = '9';
	return number;
}

#endif