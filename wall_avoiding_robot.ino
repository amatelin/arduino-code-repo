 
int rightMotorPin = 9;
int leftMotorPin = 5;
int trigPin = 2;
int echoPin = 3;
 
void setup() 
{ 
  pinMode(rightMotorPin, OUTPUT);
  pinMode(leftMotorPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
} 
 
 
void loop() 
{ 

  int distance = getDistance();
  Serial.print(distance);
  Serial.println(" mm");
  delay(1000);
  int speed = distance*5.5;
  if (speed >= 0 && speed <= 255)
  {
    analogWrite(rightMotorPin, speed);
    analogWrite(leftMotorPin, speed);
    Serial.println(speed);
  }
  
} 


// Uses an ultrasonic sensor to get the measured distance in millimeters
// TRIG and ECHO must be defined, it also blinks the pin 13 LED for pulse duration
int getDistance() {
  unsigned long t, t_start, c;
  
  // Flush sensor LOW for a second
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Pulse for 10 us
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Wait until echo signal is up.
  c = 0;
  while (digitalRead(echoPin) == LOW && c++ < 10000) {}
  
  // Measure echo signal uptime in microseconds. Also blink LED pin 13 during
  c = 0;
  t_start = micros();
  digitalWrite(13, HIGH);
  while(digitalRead(echoPin) == HIGH && c++ < 10000) {}
  digitalWrite(13, LOW);
  
  // Duration in microseconds
  t = micros() - t_start;
  
  // Distance in meters = (duration in seconds) * (speed of sound m/s) / 2
  // Distance in cm = (t * 1e-6) * (340 * 1e2) / 2 = t * 17/1000
  // Distance in millimeters = (t * 1e-6) * (340 * 1e3) / 2 = t * 17/100
  
  // Return distance in mm, sensor is supposedly accurate to 0.3cm = 3mm
  return t * 17 / 100;
}

