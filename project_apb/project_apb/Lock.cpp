/*
 * Lock.cpp
 *
 * Created: 2014-12-04 9:31:44 PM
 *  Author: amate_000
 */ 
#include "Arduino.h"
#include "Lock.h"
#include <Servo.h>

Lock::Lock(int pin)
	: controlPin(pin)
{
	servo.attach(pin);
	open();
}

void Lock::open()
{
	if (state==state_closed)
	{
		servo.write(180);
		state = state_open;
	}
}

void Lock::close()
{
	if (state==state_open)
	{
		servo.write(90);
		state = state_closed;
	}
}

bool Lock::isClosed()
{
	return (state==state_closed)?true:false;
}