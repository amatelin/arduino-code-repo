/*
 * Timer.cpp
 *
 * Created: 2014-12-04 9:34:32 PM
 *  Author: amate_000
 */ 

#include "Timer.h"
#include "Arduino.h"

Timer::Timer()
{
	state = stopped;
	int hours = 0;
	int minutes = 0;
}

void Timer::start()
{
	if (hours>0 | minutes>0)
	{
		state = running;
		referenceTime = millis();
	}

}

void Timer::stop()
{
	state = stopped;
	int hours = 0;
	int minutes = 0;
}

void Timer::setTimer(int in_h, int in_mn)
{
	hours = in_h;
	minutes = in_mn;
	convertTimeToMillis();
}

void Timer::tic()
{
	currentTime = millis();
	elapsedTime = currentTime - referenceTime;
	referenceTime = currentTime;
	remainingTime -= elapsedTime;
	convertMillisToTime();
}

void Timer::convertTimeToMillis()
{
	unsigned long total_mn = (hours*60) + minutes;
	unsigned long seconds = total_mn*60;
	remainingTime = seconds*1000;
}

void Timer::convertMillisToTime()
{
	int seconds = remainingTime/1000;
	int total_mn = seconds/60;
	minutes = total_mn%60;
	hours = (total_mn-minutes)/60;
}

int Timer::isRunning()
{
	if (state==running)
	{
		return 1;
	}
	
	else
	{
		return 0;
	}
}

int Timer::getHours()
{
	return hours;
}

int Timer::getMinutes()
{
	return minutes;
}

unsigned long Timer::getMillis()
{
	return remainingTime;
}

bool Timer::ringRing()
{
	if (remainingTime==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

