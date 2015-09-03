// Loading required libraries
#include "DHT.h"
#include <SFE_BMP180.h>
#include <Wire.h>

// Defining pins for our sensors. 
// BMP180 uses a specific protocol so no need to worry about it.
#define DHTPIN 7
#define DHTTYPE DHT11 
#define LIGHTPIN A0

#define ALTITUDE 147 // altitude used to compute pressure. 147 for Montreal

// Instantiating sensors
DHT dht(DHTPIN, DHTTYPE);
SFE_BMP180 pressure;


void setup(){
  Serial.begin(9600);
  dht.begin();
  pressure.begin();
}

void loop() {
  // Read values from sensor DHT11
  float h = dht.readHumidity();
  float t0 = dht.readTemperature();
  float hic  = dht.computeHeatIndex(t0, h, false); // option false so that result is computed in celsius
  
  // Read values from sensor BMP180
  double t1, p0, p01, p1;
  t1 = readBMPTemp();
  if (t1!=0)
  {
    double p0 = readBMPPressure(t1);
    p01 = p0;
    if (p0!=0){
       p1 = pressure.sealevel(p0,ALTITUDE); // removing the effects of altitude on pressure reading
    }
  }
  
  // Read luminosity %
  int l = getLuminosity();
  
  // Log results in serial
  Serial.println("Readings from DHT11 :");
  Serial.println("Humidity : " + String(h) + " %");
  Serial.println("Temperature (C) : " + String(t0));
  Serial.println("Heat index : " + String(hic));
  
  Serial.println("Readings from BMP180 :");
  Serial.println("Temperature (C) : " + String(t1));
  Serial.println("Pressure (abs) : " + String(p01));
  Serial.println("Pressure (corrected for altitude) : " + String(p1));
  
  Serial.println("Readings for luminosity :");
  Serial.println(String(l) + " %");

  delay(2500);
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
