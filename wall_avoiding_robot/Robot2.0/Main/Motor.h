/*
 * Motor.h
 *
 * Created: 2014-11-08 7:43:52 PM
 *  Author: amate_000
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_


class Motor {
	public:
		Motor(int, int, int);

		void initialize();
		void setSpeed(int speed);
		void setDirection(int DIRECTION);
		
	private:
		unsigned int PWM_PIN;
		unsigned int IN1_PIN;
		unsigned int IN2_PIN;
		
};


#endif /* MOTOR_H_ */