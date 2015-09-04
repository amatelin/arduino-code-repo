#include<stdlib.h>
#include <SoftwareSerial.h>
#define SSID "BELL810"
#define PASS "D9FFCC94"

SoftwareSerial esp8266(2, 3); // RX, TX
String open_tcp = "AT+CIPSTART=1,\"TCP\",\"api.thingspeak.com\",80";

void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600);
  sendDebug("AT");
  delay(5000);
  if(esp8266.find("OK")){
    Serial.println("RECEIVED: OK");
    connectWiFi();
  }
  
  delay(5000);
  sendDebug(open_tcp);
  delay(5000);
}

void loop(){

if(esp8266.available()) // check if the esp is sending a message 
  {
    while(esp8266.available())
    {
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
      Serial.write(c);
    }  
  }
  
 
}

void sendDebug(String cmd){
  Serial.print("SEND: ");
  Serial.println(cmd);
  esp8266.println(cmd);
} 
 
boolean connectWiFi(){
  esp8266.println("AT+CWMODE=1");
  delay(2000);
  esp8266.println("AT+CIPMUX=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  sendDebug(cmd);
  delay(5000);
  if(esp8266.find("OK")){
    Serial.println("RECEIVED: OK");
    return true;
  }else{
    Serial.println("RECEIVED: Error");
    return false;
  }
}
