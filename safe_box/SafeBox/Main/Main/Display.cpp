/*
 * Display.cpp
 *
 * Created: 2014-12-04 9:35:58 PM
 *  Author: amate_000
 */ 
#include "Arduino.h"
#include "Display.h"

Display::Display(const unsigned int * anodesPinArray,const unsigned int * cathodesPinArray)
{
	memcpy(anodePinRegistry, anodesPinArray, 8*sizeof(int));
	memcpy(cathodePinRegistry,  cathodesPinArray, 4*sizeof(int));	

	unsigned int anodePinsPatterns[10] = {126, 48, 109, 121, 51, 91, 95, 112, 127, 123};  // left padded with one 0
	unsigned int masks[7] = {2, 4, 8, 16, 32, 64, 128};
}

void Display::show(int number)
{
	Serial.println("Original number :");
	Serial.println(number);
	for (int i=0; i<4; i++)
	{
		int currentNumber = number%10;
		Serial.println("Current number :");
		Serial.println(number);
		clearDigits();
		activateDigit(i);
		for (int j=0; j<10; j++)
		{
			Serial.println(anodePinsPatterns[j]); // la il devrait printer 126 48 109 etc. non ?
		}
		// showNumber(currentNumber);
		number = (number-currentNumber)/10;

	}

	
}

void Display::clearDigits()
{
	for (int i=0; i<8; i++){
		digitalWrite(anodePinRegistry[i], LOW);
	}
}

void Display::activateDigit(int digit)
{
	for (int i=0; i<4; i++){
		digitalWrite(cathodePinRegistry[i], HIGH);
	}
	digitalWrite(cathodePinRegistry[digit], LOW);
}

void Display::showNumber(int number)
{
	for (int i=0; i<8; i++)
	{
		unsigned int turn_on = anodePinsPatterns[number]&masks[i];
		Serial.println(anodePinsPatterns[number]);
		Serial.println(masks[i]);
		Serial.println(turn_on);
		/*if (turn_on>0){
			digitalWrite(anodePinRegistry[i], HIGH);
			Serial.println("ANODE HIGH :"+i);
			}*/
	}
}

