/*
 * Lock.h
 *
 * Created: 2014-12-04 9:31:31 PM
 *  Author: amate_000
 */ 


#ifndef LOCK_H_
#define LOCK_H_

class Lock {
		public:
		Lock();
		virtual ~Lock();
	
		void open();
		void close();
		bool isClosed();
	
	private:
		unsigned int controlPin;
		
		enum state_t {open, closed};
		state_t state;
	};



#endif /* LOCK_H_ */