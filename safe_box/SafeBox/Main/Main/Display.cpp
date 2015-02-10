/*
 * Display.cpp
 *
 * Created: 2014-12-04 9:35:58 PM
 *  Author: amate_000
 */ 
#include "Arduino.h"
#include "Display.h"

static const unsigned int patterns[] = {126, 48, 109, 121, 51, 91, 95, 112, 127, 123};
static const unsigned int masks[] =  {64, 32, 16, 8, 4, 2, 1};
const unsigned int* Display::ANODE_PIN_PATTERNS = patterns;
const unsigned int* Display::MASKS = masks;

Display::Display(const unsigned int * anodesPinArray,const unsigned int * cathodesPinArray)
{
	memcpy(anodePinRegistry, anodesPinArray, 8*sizeof(int));
	memcpy(cathodePinRegistry,  cathodesPinArray, 4*sizeof(int));	
}

void Display::enablePins()
{
	for (int i; i<4; i++)
	{
		pinMode(cathodePinRegistry[i], OUTPUT);
	}
	for (int i; i<8; i++){
		pinMode(anodePinRegistry[i], OUTPUT);
	}
}

void Display::show(int number)
{
	clearDigits();
	activateDigit(0);
	int startDigit = 3;
	for (int i=0; i<4; i++)
	{
		int currentNumber = number%10;
		clearDigits();
		activateDigit(startDigit);
		showNumber(currentNumber);
		number = (number-currentNumber)/10;
		startDigit -= 1;
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

void Display::showDot(int digit){
	clearDigits();
	activateDigit(digit);
	digitalWrite(anodePinRegistry[7], HIGH);
}

void Display::showNumber(int number)
{
	for (int i=0; i<7; i++)
	{
		unsigned int turn_on = Display::ANODE_PIN_PATTERNS[number]&Display::MASKS[i];
		if (turn_on>0){
			digitalWrite(anodePinRegistry[i], HIGH);
		}
	}
}

