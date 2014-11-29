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
		
	private:
		Motor leftMotor;
		Motor rightMotor;
		
		DistanceSensor distanceSensor;
		
		enum state_t {stateStopped, stateRunning};
		state_t state;
		
		unsigned long startTime;
		int i;
		int max_distance;
		
};




#endif /* ROBOT_H_ */