/*
 * Robot.ino
 *
 * Created: 11/8/2014 7:36:49 PM
 * Author: amate_000
 */ 
#include "Motor.h"
#include "PinRegistry.h"
#include "Direction.h"
#include "DistanceSensor.h"
#include "NewPing.h"


class Robot
{
	public:
	
		Robot()
			: leftMotor(PinRegistry::PWM_L, PinRegistry::IN1_L, PinRegistry::IN2_L), rightMotor(PinRegistry::PWM_R, PinRegistry::IN1_R, PinRegistry::IN2_R),
			  distanceSensor()
		{
			initialize();
		}
	
		void initialize()
		{
			state = stateStopped;
			startTime = millis();
			Serial.begin(9600);
			i = 0;		
		}
	
		void run()
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
	
		
	private:
		Motor leftMotor;
		Motor rightMotor;
		
		DistanceSensor distanceSensor;
		
		enum state_t {stateStopped, stateRunning};
		state_t state;
		
		unsigned long startTime;
		int i;
		int distances[5];
		int max;
		
};

Robot robot;

void setup()
{
	robot.initialize();
}

void loop()
{	
	robot.run();
}
