/*
 * Main.ino
 *
 * Created: 11/8/2014 7:36:49 PM
 * Author: amate_000
 */ 
#include "Direction.h"
#include "PinRegistry.h"
#include "Sensors.h"
#include "NewPing.h"

Direction direction;
Sensors sensors;
NewPing sonar(PinRegistry::DIST_TRIG, PinRegistry::DIST_ECHO); 
bool bool1 = true;
bool bool2 = false;
bool going = false;
int median_ping;
int median_distance;

void setup()
{
	Serial.begin(9600);
	pinMode(PinRegistry::PWM_R, OUTPUT);
	pinMode(PinRegistry::PWM_L, OUTPUT);
	
	pinMode(PinRegistry::DIST_TRIG, OUTPUT);
	pinMode(PinRegistry::DIST_ECHO, INPUT);
}

void loop()
{
		direction.stop();
		median_ping = sonar.ping_median();
		median_distance = sonar.convert_cm(median_ping);
		//distance = sensors.getDistance();
		Serial.println(median_distance);
	
	
	delay(1000);	

	if (!going)
	{
		analogWrite(PinRegistry::PWM_R, 190);
		digitalWrite(PinRegistry::IN1_R, LOW);
		digitalWrite(PinRegistry::IN2_R, HIGH);
		
		analogWrite(PinRegistry::PWM_L, 190);
		digitalWrite(PinRegistry::IN1_L, LOW);
		digitalWrite(PinRegistry::IN2_L, HIGH);
		//direction.forward();
		going =! going;
	}
}
