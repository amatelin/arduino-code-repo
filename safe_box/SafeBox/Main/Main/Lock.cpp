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
	digitalWrite(controlPin, HIGH);
	state = state_closed;
}

void Lock::close()
{
	digitalWrite(controlPin, LOW);
}

bool Lock::isClosed()
{
	return (state==state_closed)?true:false;
}