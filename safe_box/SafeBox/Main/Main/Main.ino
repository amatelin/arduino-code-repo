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
int start_mn = 0;
int start_hr = 0;

void setup()
{

	  //Serial.begin(9600);
	  display.enablePins();
	  pinMode(PinRegistry::BUTTON1, INPUT);
	  pinMode(PinRegistry::BUTTON2, INPUT);
		
}

void loop()
{

	if (timer.isRunning()==1)
	{
		
		timer.tic();
		hours = timer.getHours();
		int time = hours*100+timer.getMinutes();
		display.show(time);
		//display.showDot(1);
		if (timer.getMinutes()!=minutes)
		{
			minutes = timer.getMinutes();
			
		}
		
	
		
		if (timer.ringRing()==true)
		{

		}
	}
	else
	{
		display.show(start_hr*100+start_mn);
		bool button1Pressed = button1.isPressed();
		bool button2Pressed = button2.isPressed();
		bool button1Held = button1.isHeld();
		bool button2Held = button2.isHeld();
		
		if (button1Held&button2Held)
		{
			timer.setTimer(start_hr, start_mn);
			timer.start();
		}
		else if (button1Pressed)
		{
			start_mn+=1;				
		}
		else if (button2Pressed)
		{
			start_hr+=1;
		}

	}
	

	 
}
