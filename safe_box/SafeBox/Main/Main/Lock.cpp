/*
 * Lock.cpp
 *
 * Created: 2014-12-04 9:31:44 PM
 *  Author: amate_000
 */ 
#include "Arduino.h"
#include "Lock.h"

void Lock::Lock()
{
	close();
}

void Lock::~Lock()
{
	
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
	if (state==closed)
	{
		return true;
	} 
	else
	{
		return false;
	}
}