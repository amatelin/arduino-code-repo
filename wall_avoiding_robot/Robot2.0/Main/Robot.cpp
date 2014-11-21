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

Robot::~DistanceSensor()
{}
	
void Robot::initialize()
{
	state = stateStopped;
	startTime = millis();
	Serial.begin(9600);
	i = 0;
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
			//Serial.println(distance);
			distances[i] = distance;
			i+=1;
			if (i>=5) 
			{
				for (int j=0; j<4; j++)
				{
					if (distances[j]<distances[j+1])
					{
						max=distances[j+1];
					}
					else
					{
						max=distances[j];
					}
				}
				i=0;
				Serial.println(max);
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
	