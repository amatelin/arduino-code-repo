/* 
* Esp8266.h
*
* Created: 2015-09-02 4:20:39 PM
* Author: amate_000
*/


#ifndef __ESP8266_H__
#define __ESP8266_H__
#include "Arduino.h"
#include <SoftwareSerial.h>

class Esp8266
{
//variables
public:
protected:
private:
	SoftwareSerial espSerial;
	bool debugMode;

//functions
public:
	Esp8266(int, int, bool);
	~Esp8266();
	
	void begin();
	bool reset();
	
	bool isOk();
	bool isBusy();
	bool isConnected(char[]);
	bool connectWifi(char[], String);
	bool openTCPConnection(String, String);
	bool closeTCPConnection();
	void send(String);
	void printDebug(String);
	
protected:
private:
	bool checkResponse(char[], int);
	

}; 

#endif //__ESP8266_H__
