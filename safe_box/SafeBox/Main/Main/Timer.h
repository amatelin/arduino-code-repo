/*
 * Timer.h
 *
 * Created: 2014-12-04 9:34:49 PM
 *  Author: amate_000
 */ 


#ifndef CLOCK_H_
#define CLOCK_H_

class Timer {
	public:
		Timer();
		
		void setTimer(int in_h, int in_mn);
		void start();
		void stop();
		void tic();
		int isRunning();
		int getHours();
		int getMinutes();
		unsigned long getMillis();
		bool ringRing();
		
	private:
		void convertTimeToMillis();
		void convertMillisToTime();
		unsigned int hours;
		unsigned int minutes;
		unsigned long remainingTime;
		unsigned long referenceTime;
		unsigned long elapsedTime;
		unsigned long currentTime;
		
		enum state_t {stopped, running};
		state_t state;  
	
	};



#endif /* CLOCK_H_ */