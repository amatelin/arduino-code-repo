/*
 * Direction.cpp
 *
 * Created: 2014-11-08 7:44:17 PM
 *  Author: amate_000
 */ 
#include "Direction.h"
#include "Arduino.h"
#include "PinRegistry.h"

Direction::Direction(): 

	globalSpeed(Direction::CRUISING_SPEED){}


Direction::~Direction()
{
}

void Direction::stop(bool right, bool left)
{
	if (right)
	{
		digitalWrite(PinRegistry::IN1_R, HIGH);
		digitalWrite(PinRegistry::IN2_R, HIGH);
	}
	if (left)
	{
		digitalWrite(PinRegistry::IN1_L, HIGH);
		digitalWrite(PinRegistry::IN2_L, HIGH);
	}
}

void Direction::forward(bool right, bool left)
{
	if (right)
	{
		analogWrite(PinRegistry::PWM_R, this->globalSpeed);
		digitalWrite(PinRegistry::IN1_R, LOW);
		digitalWrite(PinRegistry::IN2_R, HIGH);
	}
	if (left)
	{
		analogWrite(PinRegistry::PWM_L, this->globalSpeed);
		digitalWrite(PinRegistry::IN1_L, LOW);
		digitalWrite(PinRegistry::IN2_L, HIGH);
	}
}

