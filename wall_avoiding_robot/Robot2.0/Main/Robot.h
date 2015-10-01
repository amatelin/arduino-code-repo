/*
 * Robot.h
 *
 * Created: 2014-11-20 7:55:27 PM
 *  Author: amate_000
 */ 

#include "Motor.h"
#include "DistanceSensor.h"


#ifndef ROBOT_H_
#define ROBOT_H_


class Robot
{
	public:
	
		Robot();
		virtual ~Robot();
		void initialize();

	
		void run();
		void communicate(int);
		
		void forward();
		void backward();
		void start();
		void stop();
		void setSpeed(int);
		void turnLeft();
		void turnRight();
		void turnAround();
		
	private:
		Motor leftMotor;
		Motor rightMotor;
		
		DistanceSensor distanceSensor;
		
		enum state_t {stateStopped, stateRunning};
		state_t state;
		int currentDirection;
		
		static const int defaultSpeed = 150;
		
		unsigned long startTime;
		int i;
		int distance;
		unsigned long time_since_last_instruction;
		unsigned long last_instruction_time;
		
		bool expectSpeed;
		
};




#endif /* ROBOT_H_ */