//set anode interface
int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
int p = 8;
//set cathode interface
int d4 = 9;
int d3 = 10;
int d2 = 11;
int d1 = 12;
// Set variables
long n = 0;
int x = 100; 
int del = 55; // This number is fine-tuning of the clock
void setup()
{
 pinMode(d1, OUTPUT); 
 pinMode(d2, OUTPUT); 
 pinMode(d3, OUTPUT); 
 pinMode(d4, OUTPUT); 
 pinMode(a, OUTPUT); 
 pinMode(b, OUTPUT); 
 pinMode(c, OUTPUT); 
 pinMode(d, OUTPUT); 
 pinMode(e, OUTPUT); 
 pinMode(f, OUTPUT); 
 pinMode(g, OUTPUT); 
 pinMode(p, OUTPUT); 
}
void loop()
{
 clearLEDs();
 pickDigit(1);
 pickNumber((n/x/1000)%10);
 delayMicroseconds(del);
 clearLEDs();
 pickDigit(2);
 pickNumber((n/x/100)%10);
 delayMicroseconds(del);
 clearLEDs();
 pickDigit(3);
dispDec(3); 

pickNumber((n/x/10)%10);
 delayMicroseconds(del);
 clearLEDs();
 pickDigit(4);
 pickNumber(n/x%10);
 delayMicroseconds(del);
 n++;
 if (digitalRead(13) == LOW)
 { 
 n = 0;
 } 
}
void pickDigit(int x) //defing pickDigit(x), its role is turn on the dx port
{
 digitalWrite(d1, HIGH);
 digitalWrite(d2, HIGH);
 digitalWrite(d3, HIGH);
 digitalWrite(d4, HIGH);
 switch(x)
 { 
 case 1: 
 digitalWrite(d1, LOW); 
 break;
 case 2: 
 digitalWrite(d2, LOW); 
 break;
 case 3: 
 digitalWrite(d3, LOW); 
 break;
 default: 
 digitalWrite(d4, LOW); 
 break;
 } 
}
void pickNumber(int x) //define pickNumber(x), Its role is to show digital x
{
 switch(x)
 { 
   
    default: 
 zero(); 
 break;
 case 1: 
 one(); 
 break;
 case 2: 
 two(); 
 break;
 case 3: 
 three(); 
 break;
 case 4: 
four(); 
 break;
 case 5: 
 five(); 
 break;
 case 6: 
 six(); 
 break;
 case 7: 
 seven(); 
 break;
 case 8: 
 eight(); 
 break;
 case 9: 
 nine(); 
 break;
 } 
}
void dispDec(int x) // Set to open the decimal point
{
 digitalWrite(p, LOW);
}
void clearLEDs() //clear the screen 
{
 digitalWrite(a, LOW);
 digitalWrite(b, LOW);
 digitalWrite(c, LOW);
 digitalWrite(d, LOW);
 
  digitalWrite(e, LOW);
 digitalWrite(f, LOW);
 digitalWrite(g, LOW);
 digitalWrite(p, LOW);
}
void zero() // Define the number 0 cathode pin switch
{
 digitalWrite(a, HIGH);
 digitalWrite(b, HIGH);
 digitalWrite(c, HIGH);
 digitalWrite(d, HIGH);
 digitalWrite(e, HIGH);
digitalWrite(f, HIGH);
 digitalWrite(g, LOW);
}
void one() 
{
 digitalWrite(a, LOW);
 digitalWrite(b, HIGH);
 digitalWrite(c, HIGH);
 digitalWrite(d, LOW);
 digitalWrite(e, LOW);
 digitalWrite(f, LOW);
 digitalWrite(g, LOW);
}
void two() 
{
 digitalWrite(a, HIGH);
 digitalWrite(b, HIGH);
 digitalWrite(c, LOW);
 digitalWrite(d, HIGH);
 digitalWrite(e, HIGH);
 digitalWrite(f, LOW);
 digitalWrite(g, HIGH);
}
void three() 
{
 digitalWrite(a, HIGH);
 digitalWrite(b, HIGH);
 digitalWrite(c, HIGH);
 
  digitalWrite(d, HIGH);
 digitalWrite(e, LOW);
 digitalWrite(f, LOW);
 digitalWrite(g, HIGH);
}
void four() 
{
 digitalWrite(a, LOW);
 digitalWrite(b, HIGH);
 digitalWrite(c, HIGH);
 digitalWrite(d, LOW);
 digitalWrite(e, LOW);
 digitalWrite(f, HIGH);
 digitalWrite(g, HIGH);
}
void five() 
{
 digitalWrite(a, HIGH);
 digitalWrite(b, LOW);
 digitalWrite(c, HIGH);
 digitalWrite(d, HIGH);
 digitalWrite(e, LOW);
 digitalWrite(f, HIGH);
 digitalWrite(g, HIGH);
}
void six() 
{
 digitalWrite(a, HIGH);
 digitalWrite(b, LOW);
 digitalWrite(c, HIGH);
 digitalWrite(d, HIGH);
 digitalWrite(e, HIGH);
digitalWrite(f, HIGH);
 digitalWrite(g, HIGH);
}
void seven() 
{
 digitalWrite(a, HIGH);
 digitalWrite(b, HIGH);
 digitalWrite(c, HIGH);
 
  digitalWrite(d, LOW);
 digitalWrite(e, LOW);
 digitalWrite(f, LOW);
 digitalWrite(g, LOW);
}
void eight() 
{
 digitalWrite(a, HIGH);
 digitalWrite(b, HIGH);
 digitalWrite(c, HIGH);
 digitalWrite(d, HIGH);
 digitalWrite(e, HIGH);
digitalWrite(f, HIGH);
 digitalWrite(g, HIGH);
}
void nine() 
{
 digitalWrite(a, HIGH);
 digitalWrite(b, HIGH);
 digitalWrite(c, HIGH);
 digitalWrite(d, HIGH);
 digitalWrite(e, LOW);
 digitalWrite(f, HIGH);
 digitalWrite(g, HIGH);
}

