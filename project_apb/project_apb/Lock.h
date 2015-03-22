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
		Lock();
		
		void attach(int);
		void open();
		void close();
		void toggle();
		bool isClosed();
	
	private:
		Servo servo;
		
		enum state_t {state_open, state_closed};
		state_t state;
	};



#endif /* LOCK_H_ */