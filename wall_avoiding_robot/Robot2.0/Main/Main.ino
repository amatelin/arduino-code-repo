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
#include "Robot.h"

Robot robot;

void setup()
{
	robot.initialize();
}

void loop()
{	
	robot.run();
}
