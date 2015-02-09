/*
 * Main.ino
 *
 * Created: 12/4/2014 9:30:28 PM
 * Author: amate_000
 */ 
#include "Timer.h"
#include "Lock.h"
#include "Button.h"
#include "PinRegistry.h"
#include "Display.h"

Timer timer;
Lock lock(PinRegistry::LOCK);
Button button1(PinRegistry::BUTTON1);
Button button2(PinRegistry::BUTTON2);
Display display(PinRegistry::ANODES, PinRegistry::CATHODES);

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
			minutes = timer.getMinutes();
			Serial.println(minutes);
			display.show(1);
			
		}
		
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
		display.show(1);
		timer.setTimer(0, 3);
		
		timer.start();
		Serial.println("Started timer");
	}
	

	 
}
