/* 
* Esp8266.h
*
* Created: 2015-09-02 4:20:39 PM
* Author: amate_000
*/


#ifndef __ESP8266_H__
#define __ESP8266_H__


class Esp8266
{
//variables
public:
protected:
private:

//functions
public:
	Esp8266();
	~Esp8266();
	
	begin();
	void reset();
	bool isOk();
	bool isBusy();
	bool isConnected();
	bool connectWifi(String, String);
	bool openConnection(String, int);
	void send(String);
	
protected:
private:
	Esp8266( const Esp8266 &c );
	Esp8266& operator=( const Esp8266 &c );

}; //Esp8266

#endif //__ESP8266_H__
