/*
 * Main.ino
 *
 * Created: 11/8/2014 7:36:49 PM
 * Author: amate_000
 */ 
#include "Direction.h"
#include "PinRegistry.h"

Direction direction;
bool bool1 = true;
bool bool2 = false;

void setup()
{
	pinMode(PinRegistry::PWM_R, OUTPUT);
	pinMode(PinRegistry::PWM_L, OUTPUT);
}

void loop()
{
	direction.forward();
	delay(2000);
	direction.stop();
	delay(1000);
	direction.turnAround(bool1, bool2);
	bool1=!bool1;
	bool2=!bool2;
}
