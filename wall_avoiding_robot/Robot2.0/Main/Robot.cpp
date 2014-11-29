/*
 * Robot.cpp
 *
 * Created: 2014-11-20 7:55:51 PM
 *  Author: amate_000
 */ 

#include "Robot.h"
#include "Arduino.h"
#include "PinRegistry.h"


Robot::Robot()
	: leftMotor(PinRegistry::PWM_L, PinRegistry::IN1_L, PinRegistry::IN2_L), 
	  rightMotor(PinRegistry::PWM_R, PinRegistry::IN1_R, PinRegistry::IN2_R),
	  distanceSensor()
{
	initialize();
}

Robot::~Robot()
{}
	
void Robot::initialize()
{
	state = stateStopped;
	startTime = millis();
	Serial.begin(9600);
	i = 0;
	max_distance = 0;
}

void Robot::run()
{
	unsigned long currentTime = millis();
	unsigned long elapsedTime = currentTime - startTime;
	switch (state)
	{
		case stateStopped:
			if (elapsedTime>=5000)
			{
				/*
				leftMotor.setDirection(Direction::FORWARD);
				rightMotor.setDirection(Direction::FORWARD);
				leftMotor.setSpeed(190);
				rightMotor.setSpeed(190);*/
						
				state = stateRunning;
			}
			break;
		case stateRunning:
			int distance;
			distance = distanceSensor.getDistance();
			if (distance>max_distance)
			{
				max_distance=distance;
			}
			//Serial.println(distance);
			i+=1;
			if (i>=10) 
			{	
				i=0;
				Serial.println(max_distance);
				max_distance=0;
			}
/*					if (max<40)
			{
						
				leftMotor.setDirection(Direction::BACKWARD);
				rightMotor.setDirection(Direction::BACKWARD);
			}
			else
			{
				leftMotor.setDirection(Direction::FORWARD);
				rightMotor.setDirection(Direction::FORWARD);
			}*/
	}
}
	