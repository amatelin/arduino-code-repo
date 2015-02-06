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
}

bool Button::isPressed()
{
	return (digitalRead(referencePin)==HIGH) ? false:true;
}