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
#include <Adafruit_NeoPixel/Adafruit_NeoPixel.h>

Timer timer;
Lock lock;
Button button2;
Button button1;

Adafruit_NeoPixel pixels(1, 4, NEO_RGB + NEO_KHZ800);

Display display(PinRegistry::CATHODES, PinRegistry::ANODES);

int hours;
int minutes;
int start_mn = 0;
int start_hr = 0;
int i = 0;
int time_passed = 0;
int clock_ref = millis();
double voltage;
double discharge_threshold = 3.75;
int chargerMode;

enum charger_state_t {charging, finished, idle};
charger_state_t charger_state = idle;

enum battery_state_t {charged, discharged};
battery_state_t battery_state = charged;

void setup()
{

	//Serial.begin(9600);
	button1.attach(PinRegistry::BUTTON1);
	button2.attach(PinRegistry::BUTTON2);
	
	display.enablePins();
	
	pinMode(PinRegistry::BATTERY, INPUT);

	  
	pinMode(PinRegistry::BUTTON1, INPUT);
	pinMode(PinRegistry::BUTTON2, INPUT);
	lock.attach(PinRegistry::LOCK);
	
	pixels.begin(); // This initializes the NeoPixel library.
	pixels.show();
	pixels.setBrightness(15);
			

}

void loop()
{         

	
	if (time_passed==0){

		voltage = readVoltage();
		
		if (voltage>discharge_threshold) {
			battery_state = charged;
		}
		else {
			battery_state = discharged;
		}
		
	} 

	
	if (time_passed>5000) {
		time_passed = 0;
		clock_ref = millis();
	} 
	else {
			time_passed = millis() - clock_ref;
	}
	
	if (battery_state == discharged) {
		display.clearDigits();
		pixels.setPixelColor(0, 0, 255, 0);
		timer.stop();
		lock.open();

	}
	else {
		pixels.setPixelColor(0, 255, 0, 0);
		
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
				lock.open();
				display.printOpen();
				pixels.setPixelColor(0, 255, 0, 0);
				if (button1Held&button2Held)
				{
					timer.stop();
				}
			}
			else
			{
				if (button1Held||button2Held) {
					pixels.setPixelColor(0, 0, 255, 0);
				} 
				else {
					pixels.setPixelColor(0, 255, 255, 255);
				}
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
					//lock.toggle();
					
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

	pixels.show();
}

float readVoltage() {
	float value = analogRead(PinRegistry::BATTERY);
	
	float voltage = ((value/1024)*5)*3.2;
	
	return voltage;
}
