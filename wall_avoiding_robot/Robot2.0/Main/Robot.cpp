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
	expectSpeed = false;
}

void Robot::run()
{
	unsigned long currentTime = millis();
	unsigned long elapsedTime = currentTime - startTime;
	communicate();
	/*
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
			5time_since_last_instruction =millis()-last_instruction_time;
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
		}*/
}

void Robot::communicate()
{
	int code;
	if (Serial.available()>0)
	{
		if (expectSpeed==true)
		{
			code = Serial.parseInt();
			expectSpeed=false;
			setSpeed(code);
		}
		else
		{
			code = Serial.read();
		}
	}
	if (code=='S')
	{
		expectSpeed=true;
	}
	switch(code)
	{
		case '1':
			start();
			break;
		case '0':
			stop();
			break;
		case 'F':
			forward();
			break;
		case 'B':
			backward();
			break;
		case 'R':
			turnRight();
			break;
		case 'l':
			turnLeft();
			break;
	}
}

void Robot::forward()
{
	leftMotor.setDirection(Direction::FORWARD);
	rightMotor.setDirection(Direction::FORWARD);
}

void Robot::backward()
{
	leftMotor.setDirection(Direction::BACKWARD);
	rightMotor.setDirection(Direction::BACKWARD);
}

void Robot::start()
{
	leftMotor.setSpeed(defaultSpeed);
	rightMotor.setSpeed(defaultSpeed);	
}

void Robot::stop()
{
	leftMotor.setSpeed(0);
	rightMotor.setSpeed(0);
}

void Robot::setSpeed(int speed)
{
	leftMotor.setSpeed(speed);
	rightMotor.setSpeed(speed);
}

void Robot::turnLeft()
{
	leftMotor.setDirection(Direction::BACKWARD);
	rightMotor.setDirection(Direction::FORWARD);
}

void Robot::turnRight()
{
	leftMotor.setDirection(Direction::FORWARD);
	rightMotor.setDirection(Direction::BACKWARD);
}

void Robot::turnAround()
{
	
}
