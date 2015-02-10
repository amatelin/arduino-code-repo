/*
 * Button.cpp
 *
 * Created: 2014-12-04 9:33:55 PM
 *  Author: amate_000
 */ 

#include "Button.h"
#include "Arduino.h"

Button::Button(int pin)
	: referencePin(pin)
{
	triggered = false;
}

bool Button::isPressed()
{
	if (!triggered&digitalRead(referencePin)==HIGH)
	{
		triggered=true;
		return true;
	}
	else if (triggered&digitalRead(referencePin)==LOW)
	{
		triggered=false;
		return false;
	}
	return false;
}

bool Button::isHeld()
{
	return (digitalRead(referencePin)==HIGH) ? false:true;
}