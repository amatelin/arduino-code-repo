/*
 * project_abp.ino
 *
 * Created: 12/4/2014 9:30:28 PM
 * Author: amate_000
 */ 
#include <Servo.h>
#include "Timer.h"
#include "Lock.h"
#include "Button.h"
#include "PinRegistry.h"
#include "Display.h"

Timer timer;
Lock lock;
Button button2;
Button button1;

Display display(PinRegistry::CATHODES, PinRegistry::ANODES);

int hours;
int minutes;
int start_mn = 0;
int start_hr = 0;
int i = 0;

void setup()
{

	//Serial.begin(9600);
	button1.attach(PinRegistry::BUTTON1);
	button2.attach(PinRegistry::BUTTON2);
	display.enablePins();
	  
	pinMode(PinRegistry::BUTTON1, INPUT);
	pinMode(PinRegistry::BUTTON2, INPUT);
	lock.attach(PinRegistry::LOCK);

}

void loop()
{
	
	bool button1Pressed = button1.isPressed();
	bool button2Pressed = button2.isPressed();
	int button1Held = button1.isHeld();
	int button2Held = button2.isHeld();
	
	
	if (timer.isRunning()==1)
	{
		if (timer.ringRing()==true)
		{
			start_hr = 0;
			start_mn = 0;
			display.showColon();
			lock.open();
			display.printOpen();
			if (button1Held&button2Held)
			{
				timer.stop();
			}
		}
		else
		{
			timer.tic();
			hours = timer.getHours();
			int time = hours*100+timer.getMinutes()+1;
			display.show(time);
			display.showColon();
			if (timer.getMinutes()!=minutes)
			{
				minutes = timer.getMinutes();
						
			}
		}
		
		
	}
	else
	{
		display.show(start_hr*100+start_mn);
		display.showColon();
		
		if (button1Held&button2Held)
		{
			if (button1Pressed)
			{
				lock.toggle();
			}
			else if (button2Pressed)
			{
				timer.setTimer(start_hr, start_mn);
				timer.start();
				lock.close();
			}
		}
		else if (button1Pressed)
		{
			if (start_mn==59)
			{
				start_hr += 1;
				start_mn = 0;
			}
			else
			{
				start_mn+=1;
			}
		}
		else if (button2Pressed)
		{
			start_hr+=1;
		}
	} 
}
