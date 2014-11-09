/*
 * Main.ino
 *
 * Created: 11/8/2014 7:36:49 PM
 * Author: amate_000
 */ 
#include "Direction.h"
#include "PinRegistry.h"

Direction direction;

void setup()
{
	pinMode(PinRegistry::PWM_R, OUTPUT);
	pinMode(PinRegistry::PWM_L, OUTPUT);
}

void loop()
{
	direction.forward(false, true);
	delay(1000);
	direction.stop();
	delay(1000);
	direction.forward(true, false);
	delay(1000);
	direction.stop();
}
