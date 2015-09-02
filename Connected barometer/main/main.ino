/*
 * main.ino
 *
 * Created: 9/2/2015 3:48:41 PM
 * Author: amate_000
 */ 
// Loading required libraries
#include "DHT.h"
#include <SFE_BMP180.h>
#include <Wire.h>
#include <SoftwareSerial.h>

// Defining pins for our sensors.
// BMP180 uses a specific protocol so no need to worry about it.
#define DHTPIN 5
#define LIGHTPIN A0
#define DHTTYPE DHT11

#define ALTITUDE 147 // altitude used to compute pressure. 147 for Montreal

// Defining connection settings
#define SSID ""
#define PASS ""
#define IP "api.thingspeak.com"
#define PORT = 80
#define API_KEY = ""

// Defining delay time between each loop
#define WAIT = 30000;

// Enable debug mode if true (will print debug messages to Serial)
bool debug = false;

// Instantiating sensors
DHT dht(DHTPIN, DHTTYPE);
SFE_BMP180 pressure;


Esp8266 esp8266(8, 9, false);
//SoftwareSerial esp8266(8,9);


void setup()
{
	// Try to connect Esp. If it is non-responding, reset
	esp8266.begin();
	if (esp8266.isOk()){
		esp8266.connectWifi(SSID, PASS);
	} else {
		esp8266.reset();
	}
	
	// Start sensors
	pressure.begin();
	dht.begin();

}

void loop()
{
	int l;
	float h;
	double t, p0, p1;
	// Read luminosity value
	l = getLuminosity();
	// Read values from sensor DHT11
	h = dht.readHumidity();
	// Read values from sensor BMP180
	t = readBMPTemp();
	if (t=0) // if we got a valid temperature, go for pressure
	{
		double p0 = readBMPPressure(t);
		if (p0!=0) // if we got a valid pressure, go for adjusted pressure
		{
			p1 = pressure.sealevel(p0,ALTITUDE); // removing the effects of altitude on pressure reading
		}
	}
	
	if (!esp8266.isBusy())
	{
		if (esp8266.isConnected())
		{
			pushData(t, h, p1, l);
		} else 
		{
			status = esp8266.connectWifi(SSID, PASS);
			if (!status) esp8266.reset();
		}
	}

	
	delay(WAIT);
}

void pushData(String temp, String humid, String pres, String lum)
{
	String call = "GET /update?key=" + API_KEY;
	call += "&field1=";
	call += temp;
	call += "&field2=";
	call += humid;
	call += "&field3=";
	call += pres;
	call += "&field4=";
	call += lum;
	call += "\r\n";
	
	status = esp8266.openConnection(IP, PORT);
	if (!status) return;
	
	esp8266.send(call);
}

double readBMPTemp() {
	
	char status;
	double T;
	
	// Start a temperature measurement:
	// If request is successful, the number of ms to wait is returned.
	// If request is unsuccessful, 0 is returned.

	status = pressure.startTemperature();
	if (status != 0)
	{
		// Wait for the measurement to complete:
		delay(status);

		// Retrieve the completed temperature measurement:
		// Note that the measurement is stored in the variable T.
		// Function returns 1 if successful, 0 if failure.

		status = pressure.getTemperature(T);
		
		return (status!=0 ? T : 0);
		
	}
}

double readBMPPressure(double temp) {
	
	char status;
	double P;
	
	// Start a pressure measurement:
	// The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
	// If request is successful, the number of ms to wait is returned.
	// If request is unsuccessful, 0 is returned.
	
	status = pressure.startPressure(3);
	if (status != 0)
	{
		// Wait for the measurement to complete:
		delay(status);
		
		// Retrieve the completed pressure measurement:
		// Note that the measurement is stored in the variable P.
		// Note also that the function requires the previous temperature measurement (T).
		// (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
		// Function returns 1 if successful, 0 if failure.
		
		status = pressure.getPressure(P,temp);
		return (status!=0 ? P : 0);
	}
}

int getLuminosity()
{
	int reading = analogRead(LIGHTPIN);
	int value = map(reading, 0, 1023, 0, 100);
	return value;
}