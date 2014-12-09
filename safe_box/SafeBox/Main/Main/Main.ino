/*
 * Main.ino
 *
 * Created: 12/4/2014 9:30:28 PM
 * Author: amate_000
 */ 
#include "Timer.h"

Timer timer;
int hours;
int minutes;

void setup()
{

	  Serial.begin(9600);
}

void loop()
{
	
	if (timer.isRunning()==1)
	{
		timer.tic();
		hours = timer.getHours();
		if (timer.getMinutes()!=minutes)
		{
			Serial.println(timer.getMinutes());
		}
		minutes = timer.getMinutes();
		
		if (timer.ringRing()==true)
		{
			while (true)
			{
				Serial.println("Rrrrrrrring");
			}

		}
	}
	else
	{
		timer.setTimer(0, 3);
		timer.start();
	}
	

	 
}
