/*
 * Sensors.cpp
 *
 * Created: 2014-11-09 11:14:38 AM
 *  Author: amate_000
 */ 

#include "Sensors.h"
#include "PinRegistry.h"
#include "Arduino.h"


Sensors::Sensors()
{}

Sensors::~Sensors()
{}
	
int Sensors::getDistance()
{
	unsigned long t, t_start, c;
	  
	// Flush sensor LOW for a second
	digitalWrite(PinRegistry::DIST_TRIG, LOW);
	delayMicroseconds(2);
	  
	// Pulse for 10 us
	digitalWrite(PinRegistry::DIST_TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(PinRegistry::DIST_TRIG, LOW);
	  
	// Wait until echo signal is up.
	c = 0;
	while (digitalRead(PinRegistry::DIST_ECHO) == LOW && c++ < 10000) {}
	  
	// Measure echo signal uptime in microseconds. Also blink LED pin 13 during
	c = 0;
	t_start = micros();
	while(digitalRead(PinRegistry::DIST_ECHO) == HIGH && c++ < 10000) {}
	  
	// Duration in microseconds
	t = micros() - t_start;
	  
	// Distance in meters = (duration in seconds) * (speed of sound m/s) / 2
	// Distance in cm = (t * 1e-6) * (340 * 1e2) / 2 = t * 17/1000
	// Distance in millimeters = (t * 1e-6) * (340 * 1e3) / 2 = t * 17/100
	  
	// Return distance in mm, sensor is supposedly accurate to 0.3cm = 3mm
	return t * 17 / 100;
}	