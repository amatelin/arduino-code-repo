/*
 * DistanceSensor.cpp
 *
 * Created: 2014-11-09 11:14:38 AM
 *  Author: amate_000
 */ 

#include "DistanceSensor.h"
#include "PinRegistry.h"
#include "Arduino.h"
#include "NewPing.h"

DistanceSensor::DistanceSensor()
	: sensor(PinRegistry::DIST_TRIG, PinRegistry::DIST_ECHO, 100), maxDistance(100)
{}

DistanceSensor::~DistanceSensor()
{}
	
unsigned int DistanceSensor::getDistance()
{
	int distance = sensor.ping_cm();
	if (distance<= 0)
	{
		return maxDistance;
	}
	return distance;
}
