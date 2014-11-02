int PWM_A = 5;
int IN1_A = 7;
int IN2_A = 8;
int PWM_B = 6;
int IN1_B = 9;
int IN2_B = 10;


void setup()
{
pinMode(PWM_A, OUTPUT);
pinMode(PWM_B, OUTPUT);
}

void loop() {

  digitalWrite(IN1_A, HIGH);
  digitalWrite(IN2_A, LOW);
  analogWrite(PWM_A, 150);
  
  digitalWrite(IN1_B, HIGH);
  digitalWrite(IN2_B, LOW);
  analogWrite(PWM_B, 150);
  
}


