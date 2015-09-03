/* 
* Esp8266.cpp
*
* Created: 2015-09-02 4:20:39 PM
* Author: amate_000
*/


#include "Esp8266.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

Esp8266::Esp8266(int rxPin, int txPin, bool debugMode) : espSerial(rxPin, txPin), debugMode(debugMode)
{
	
} 

Esp8266::~Esp8266() 
{
	
}

/*
public method begin() : 
Start communications. Only SoftwareSerial communications toward esp if debugMode = false
*/
void Esp8266::begin()
{
	espSerial.begin(9600);
	if (debugMode) 
	{
		Serial.begin(9600);
		Serial.println("Serial com open");
	}
}

/*
private method checkResponse(char, int) :
Look for a response code in the stream from espSerial
Print de debug message to Serial if debugMode = true
*/
bool Esp8266::checkResponse(char response[], int wait)
{
	delay(wait);
	bool status = espSerial.find(response);
	
	// Print the result to Serial
	String msg = "'" + String(response) + "' : ";
	msg += (status ? "Found" : "Not found");
	printDebug(msg);
	
	return (status ? true : false);
}	


/*
private method printDebug(String) : 
Print a debug message to Serial if debug = true (option set in class constructor) 
*/
void Esp8266::printDebug(String msg)
{
	if (debugMode) Serial.println(msg);
}

/*
public method reset() :
Send reset code to esp and check response
*/
bool Esp8266::reset()
{
	bool status; 
	
	espSerial.println("AT+RST");	
	printDebug("Sent : RESET");
	
	status = checkResponse("ready", 3000);
	
	if (status) printDebug("Device is ready");
	return status;
}

/*
public method isOK() :
Send 'AT' code to esp and look for 'OK' in response
*/
bool Esp8266::isOk()
{
	bool status;
	
	espSerial.println("AT");
	printDebug("Sent : AT");
	
	status = checkResponse("OK", 2000);
	
	if (status) printDebug("Device is ok");
	return status;
}

/*
public method isBusy() :
Send 'AT' code to esp and look for 'busy' in response
*/
bool Esp8266::isBusy()
{
	bool status;
	
	espSerial.println("AT");
	printDebug("Sent : AT");
	
	status = checkResponse("busy", 2000);
	
	if (status) printDebug("Device is busy");
	return status;
}

/*
public method isConnected(SSID) :
Send AT command to check for connection and compares to given SSID
*/
bool Esp8266::isConnected(char SSID[])
{
	printDebug("Checking wifi connection...");
	espSerial.println("AT+CWJAP?");
	
	bool status = checkResponse(SSID, 2500);
	
	String msg = (status ? "Wifi connected" : "Wifi not connected");
	printDebug(msg);
	
	return status;
}

/*
public method connectWifi(char[], String) :
Connect esp to wifi providing network SSID and passkey
Will try 4 times and check if SSID is the one connected to afterward
*/
bool Esp8266::connectWifi(char SSID[], String PASS)
{
	int attempts = 0;
	String cmd, msg; 
	bool status;
	
	printDebug("Connecting wifi");
	cmd = "AT+CWMODE=1";
	espSerial.println(cmd);
	printDebug("Sent : " + cmd);
	delay(2000);
	
	cmd = "AT+CWJAP=\"" + String(SSID) + "\",\"" + PASS + "\"";
	
	while (attempts<4)
	{
		espSerial.println(cmd);
		printDebug("Sent : " + cmd);
		
		if (checkResponse("OK", 5000)) break;
		
		attempts++;
		printDebug("Connection : " + String(attempts) + " attempt(s)");	
	}
	
	status = isConnected(SSID);
	
	msg = "Connection : ";
	msg += (status ? "Success" : "Error");
	printDebug(msg);
	
	return status;
}

/*
public method openConnection(String, String) : 
Opens TCP connection with provided parameters
Check afterward if 'CONNECTED' code returned by esp
*/
bool Esp8266::openTCPConnection(String IP, String PORT)
{
	String cmd, msg;
	bool status;
	
	msg = "Opening TCP connection - IP:'" + IP + "' PORT:" + PORT;
	cmd = "AT+CIPSTART=\"TCP\",\"" + IP + "\"," + PORT;
	printDebug(msg);
	espSerial.println(cmd);
	printDebug("Sent :" + cmd);
	
	status = checkResponse("CONNECT", 2500);
	
	msg = "TCP connection :";
	msg += (status ? "success" : "failed");
	printDebug(msg);
	
	return status;
}

/*
public method closeTCPConnection() : 
Send code to close connection to esp and checks if 'CLOSED' code is returned
*/
bool Esp8266::closeTCPConnection()
{
	printDebug("Closing TCP connection");
	espSerial.println("AT+CIPCLOSE");
	
	return checkResponse("CLOSED", 5000);
}

/*
public method send(String)
Print string to open TCP connection
Announces string length, checks for cursor and wait for confirmation code 'SEND OK'
*/
void Esp8266::send(String content)
{
	String cmd;
	String msg = "Sent : ";
	bool status;
	
	printDebug("Writing to TCP connection");
	printDebug("Content to write :");
	printDebug(content);
	cmd = "AT+CIPSEND=" + String(content.length());
	espSerial.println(cmd);
	printDebug("Sent : " + cmd);
	
	status = checkResponse(">", 10);
	if (status)
	{
		espSerial.print(content);
		printDebug("Content sent");

	} else {
		printDebug("Cursor error");
		closeTCPConnection();
	}
	
}
