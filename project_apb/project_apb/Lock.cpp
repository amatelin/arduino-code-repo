/*
 * Lock.cpp
 *
 * Created: 2014-12-04 9:31:44 PM
 *  Author: amate_000
 */ 
#include "Arduino.h"
#include "Lock.h"
#include <Servo.h>

Lock::Lock()
{
}

void Lock::attach(int pin)
{
	servo.attach(pin);
	state = state_closed;
	open();
}

void Lock::open()
{
	if (state==state_closed)
	{
		servo.write(70);
		state = state_open;
	}
}

void Lock::toggle()
{
	(state==state_closed) ? open():close();
}

void Lock::close()
{
	if (state==state_open)
	{
		servo.write(170);
		state = state_closed;
	}
}

bool Lock::isClosed()
{
	return (state==state_closed)?true:false;
}