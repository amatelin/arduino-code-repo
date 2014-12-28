/*
 * Lock.cpp
 *
 * Created: 2014-12-04 9:31:44 PM
 *  Author: amate_000
 */ 
#include "Arduino.h"
#include "Lock.h"

void Lock::Lock(int pin)
	: controlPin(pin)
{
	close();
}

void Lock::open()
{
	digitalWrite(controlPin, HIGH);
	state = closed;
}

void Lock::close()
{
	digitalWrite(controlPin, LOW);
}

bool Lock::isClosed()
{
	return (state==closed)?true:false;
}