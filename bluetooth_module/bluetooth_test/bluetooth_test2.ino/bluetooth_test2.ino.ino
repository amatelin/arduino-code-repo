  /*
 HC-05.ino
 
 (C)2014 noro24.de, http://www.noro24.de
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version. http://www.gnu.org/licenses/
 
Arduino pins: 
 - RX is digital pin 10 (connect to Bluetooth TX )
 - TX is digital pin 11 (connect to Bluetooth RX)
 */
 
#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); // RX, TX

int KEY_PIN = 4; // set mode of the Bluetooth (AT or Pairing mode)

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(38400); // for AT mode
  /*while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }*/

  // set the data rate for HC-05
  BT.begin(38400);

  pinMode(KEY_PIN, OUTPUT);
  
  digitalWrite(KEY_PIN, HIGH); // AT mode
  //digitalWrite(KEY_PIN, LOW); // Pairing mode
  
  delay(500);
}

void loop() 
{
  if (BT.available())
    Serial.write(BT.read()); // write all on the SerialMonitor what is getting from Bluetooth
  if (Serial.available())
    BT.write(Serial.read()); // write to Bluetooth all is getting from SerialMonitor
}

