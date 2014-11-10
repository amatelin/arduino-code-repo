/*
 * DistanceSensor.h
 *
 * Created: 2014-11-09 8:34:11 AM
 *  Author: amate_000
 */ 
#include "NewPing.h"

#ifndef DISTANCESENSOR_H_
#define DISTANCESENSOR_H_

class DistanceSensor {
	public:
		DistanceSensor();
		virtual ~DistanceSensor();
		
		unsigned int getDistance();
		
	private:
		NewPing sensor;
		int maxDistance;	
		
};



#endif /* SENSORS_H_ */