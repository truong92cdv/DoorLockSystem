#ifndef __SERVO_H__
#define __SERVO_H__

#include <reg52.h>
#include <port.h>
#include <intrins.h>
#include <delay.h>

/* Define value to be loaded in timer for PWM period of 20 milli second */
#define PWM_Period 0xB7FE

unsigned int ON_Period, OFF_Period, DutyCycle;

void Timer_init();
void Set_DutyCycle_To(float duty_cycle);
void Servo_init();
void Servo_close();
void Servo_open();

void Timer_init()
{
	TMOD &= 0xF1;
	TMOD |= 0x01;				/* Timer0 mode1 */
	TH0 = (PWM_Period >> 8);	/* 20ms timer value */
	TL0 = PWM_Period;
	TR0 = 1;					/* Start timer0 */
}

void Timer0_ISR() interrupt 1	
{
	SERVO_PIN = !SERVO_PIN;
	if(SERVO_PIN)
	{
		TH0 = (ON_Period >> 8);
		TL0 = ON_Period;
	}	
	else
	{
		TH0 = (OFF_Period >> 8);
		TL0 = OFF_Period;
	}	
			
}

/* Calculate ON & OFF period from duty cycle */
void Set_DutyCycle_To(float duty_cycle)
{
	float period = 65535 - PWM_Period;
	ON_Period = ((period/100.0) * duty_cycle);
	OFF_Period = (period - ON_Period);	
	ON_Period = 65535 - ON_Period;	
	OFF_Period = 65535 - OFF_Period;
}

void Servo_init()
{
	EA = 1;
	ET0 = 1;
	Timer_init();
	Set_DutyCycle_To(5);
}

void Servo_close()
{
	Set_DutyCycle_To(5);
}

void Servo_open()
{
	Set_DutyCycle_To(10);
}

#endif