/*
 * Lock.cpp
 *
 * Created: 2014-12-04 9:31:44 PM
 *  Author: amate_000
 */ 
#include "Arduino.h"
#include "Lock.h"

Lock::Lock(int pin)
	: controlPin(pin)
{
	close();
}

void Lock::open()
{
	if (state==state_closed)
	{
		digitalWrite(controlPin, HIGH);
		state = state_open;
	}
}

void Lock::close()
{
	if (state==state_open)
	{
		digitalWrite(controlPin, LOW);
		state = state_closed;
	}
}

bool Lock::isClosed()
{
	return (state==state_closed)?true:false;
}