/*
 * Lock.h
 *
 * Created: 2014-12-04 9:31:31 PM
 *  Author: amate_000
 */ 
#include "Servo.h"

#ifndef LOCK_H_
#define LOCK_H_

class Lock {
	public:
		Lock(int);
	
		void open();
		void close();
		bool isClosed();
	
	private:
		unsigned int controlPin;
		Servo servo;
		
		enum state_t {state_open, state_closed};
		state_t state;
	};



#endif /* LOCK_H_ */