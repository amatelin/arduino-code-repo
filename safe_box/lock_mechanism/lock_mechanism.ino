char incomingByte = 0;   // for incoming serial data
char one = 1;
char zero = 0;
int controlPin = 7;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  pinMode(controlPin, OUTPUT);
}

void loop() {

        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
                incomingByte = incomingByte - 48;
                if (incomingByte == one)
                {
                  Serial.println("Yay");
                  digitalWrite(controlPin, HIGH);
                }
                else if (incomingByte == zero)
                {
                  Serial.println("Closed");
                  digitalWrite(controlPin, LOW);
                }

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
        }
}
 
