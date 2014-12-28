/*
 * Motor.cpp
 *
 * Created: 2014-11-08 7:44:17 PM
 *  Author: amate_000
 */ 
#include "Motor.h"
#include "Arduino.h"
#include "PinRegistry.h"

Motor::Motor(int pwm, int in1, int in2)
	: PWM_PIN(pwm), IN1_PIN(in1), IN2_PIN(in2)
{
}

void Motor::initialize()
{
	pinMode(PWM_PIN, OUTPUT);
}


void Motor::setSpeed(int speed)
{
	analogWrite(PWM_PIN, speed);
}

void Motor::setDirection(int DIRECTION)
{
	switch(DIRECTION)
	{
		case 1:
			digitalWrite(IN1_PIN, LOW);
			digitalWrite(IN2_PIN, HIGH);
			break;
		case -1:
			digitalWrite(IN1_PIN, HIGH);
			digitalWrite(IN2_PIN, LOW);
			break;
		default:
			digitalWrite(IN1_PIN, LOW);
			digitalWrite(IN2_PIN, HIGH);
			break;
	}
}