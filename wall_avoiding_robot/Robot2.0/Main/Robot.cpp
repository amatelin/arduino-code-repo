/*
 * Robot.cpp
 *
 * Created: 2014-11-20 7:55:51 PM
 *  Author: amate_000
 */ 

#include "Robot.h"
#include "Arduino.h"
#include "PinRegistry.h"
#include "Direction.h"
#include "math.h"


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
	distance = 100;
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
				
				leftMotor.setDirection(Direction::FORWARD);
				rightMotor.setDirection(Direction::FORWARD);
				leftMotor.setSpeed(190);
				rightMotor.setSpeed(200);
				time_since_last_instruction = 0;
				last_instruction_time = millis();
						
				state = stateRunning;
			}
			break;
		case stateRunning:
			distance = distanceSensor.getDistance();
			time_since_last_instruction =millis()-last_instruction_time;
			Serial.println(distance);
			Serial.println(time_since_last_instruction);

			if (distance<35&time_since_last_instruction>250)
			{
				int start_time = millis();		
				int timeVar = 0;
				leftMotor.setDirection(Direction::BACKWARD);
				rightMotor.setDirection(Direction::BACKWARD);
				while (timeVar<750)
				{
					timeVar = millis()-start_time;
				}
				timeVar = 0;
				leftMotor.setDirection(Direction::BACKWARD);
				rightMotor.setDirection(Direction::FORWARD);
				while (timeVar<1485)
				{
					timeVar = millis()-start_time;
				}
				leftMotor.setDirection(Direction::FORWARD);
				rightMotor.setDirection(Direction::FORWARD);
				
				
				time_since_last_instruction = 0;
				last_instruction_time = millis();
			}
			else if(distance>35)
			{
				Serial.println("F");
				leftMotor.setDirection(Direction::FORWARD);
				rightMotor.setDirection(Direction::FORWARD);
				time_since_last_instruction=0;
				last_instruction_time = millis();
			}
		}
}
	