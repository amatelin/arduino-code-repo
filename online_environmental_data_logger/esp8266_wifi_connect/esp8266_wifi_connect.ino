#include<stdlib.h>
#include <SoftwareSerial.h>
#define SSID ""
#define PASS ""
SoftwareSerial esp8266(2, 3); // RX, TX

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
}

void loop(){

}

void sendDebug(String cmd){
  Serial.print("SEND: ");
  Serial.println(cmd);
  esp8266.println(cmd);
} 
 
boolean connectWiFi(){
  esp8266.println("AT+CWMODE=1");
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
