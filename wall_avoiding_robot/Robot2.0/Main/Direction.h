/*
 * Direction.h
 *
 * Created: 2014-11-08 7:43:52 PM
 *  Author: amate_000
 */ 


#ifndef DIRECTION_H_
#define DIRECTION_H_


class Direction {
	public:
		Direction();
		virtual ~Direction();
		
		void stop(bool right=true, bool left=true);	
		void forward(bool right=true, bool left=true);
		void turnAround(bool right, bool left);
		
		//void left();
		//void right();
		
		
	private:
		unsigned int globalSpeed;
		
		static const unsigned int MIN_SPEED = 150;
		static const unsigned int MAX_SPEED = 255;
		static const unsigned int CRUISING_SPEED = 200;	
		static const unsigned int UTURN_TIME = 1500;

};


#endif /* DIRECTION_H_ */