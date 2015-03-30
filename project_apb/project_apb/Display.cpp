/*
 * Display.cpp
 *
 * Created: 2014-12-04 9:35:58 PM
 *  Author: amate_000
 */ 
#include "Arduino.h"
#include "Display.h"

static const unsigned int patterns[] = {126, 48, 109, 121, 51, 91, 95, 112, 127, 123, 103, 79, 118};
static const unsigned int openChar[] = {0, 10, 11, 12};
static const unsigned int masks[] =  {64, 32, 16, 8, 4, 2, 1};
const unsigned int* Display::CATHODE_PIN_PATTERNS = patterns;
const unsigned int* Display::MASKS = masks;

Display::Display(const unsigned int * cathodesPinArray, const unsigned int * anodesPinArray)
{
	memcpy(cathodePinRegistry, cathodesPinArray, 8*sizeof(int));
	memcpy(anodePinRegistry,  anodesPinArray, 5*sizeof(int));	
}

void Display::enablePins()
{
	for (int i; i<5; i++)
	{
		pinMode(anodePinRegistry[i], OUTPUT);
	}
	for (int i; i<8; i++){
		pinMode(cathodePinRegistry[i], OUTPUT);
	}
}

void Display::show(int number)
{
	for (int i=3; i>=0; i--)
	{
		int currentNumber = number%10;
		clearDigits();
		activateDigit(i);
		showNumber(currentNumber);
		number = (number-currentNumber)/10;
	}
}

void Display::clearDigits()
{
	for (int i=0; i<8; i++){
		digitalWrite(cathodePinRegistry[i], LOW);
	}
}

void Display::activateDigit(int digit)
{
	for (int i=0; i<5; i++){
		digitalWrite(anodePinRegistry[i], HIGH);
	}
	digitalWrite(anodePinRegistry[digit], LOW);
}

void Display::showColon(){
	clearDigits();
	digitalWrite(anodePinRegistry[4], LOW);
	digitalWrite(cathodePinRegistry[7], HIGH);
}

void Display::showNumber(int number)
{
	for (int i=0; i<7; i++)
	{
		unsigned int turn_on = Display::CATHODE_PIN_PATTERNS[number]&Display::MASKS[i];
		if (turn_on>0){
			digitalWrite(cathodePinRegistry[i], HIGH);
		}
		else
		{
			digitalWrite(cathodePinRegistry[i], LOW);
		}
	}
}

void Display::printOpen()
{
	for (int i=0; i<4; i++)
	{
		clearDigits();
		activateDigit(i);
		showNumber(openChar[i]);
	}
}

