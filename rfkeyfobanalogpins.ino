/*
  RFKeyfob
 Provides an example of how to read the XL-R02 RF module 
 with signals from the four button key remote.
 Reads a digital input on pins 2-6, prints the result 
 to the serial monitor. Irt is based on the PT 2272 chip.
 The application uses the analog pins 
 since some shields use the digital pins.
 Author: Bobby Kawamura 6/21/2014
 Wire the rf module to the arduino as follows:
 
 GND - GND
 5V - 5V
 D0 - A0
 D1 - A1
 D2 - A2
 D4 - A3
 VT - A4
 Relay - A5
 This example code is in the public domain.
 */

// digital pin 2-6 has a outputd from the XL-R02A attached to it. 
// Give it a name describe by the pinouts on the RF module:

const int relay_pin = 8; // Relay pin

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  // Pin5 is used to control a relay module
  pinMode(A5, OUTPUT);
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  digitalWrite(A4,HIGH);
  digitalWrite(A5,LOW);
  //pinMode(A5,OUTPUT);
  // Wait for 1 second
  delay(1000); 
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonD = digitalRead(A0);
  int buttonC = digitalRead(A1);
  int buttonB = digitalRead(A2);
  int buttonA = digitalRead(A3);
  int PinStateVT = digitalRead(A4);
  // print out the state of the buttons:
  Serial.print("A=");
  Serial.print(buttonA);
  Serial.print("\tB=");
  Serial.print(buttonB);
  Serial.print("\tC=");
  Serial.print(buttonC);
  Serial.print("\tD=");
  Serial.print(buttonD);
  Serial.print("\tVT=");
  Serial.print(PinStateVT);
  Serial.println();
  if ( buttonA == 1 )
  {
    digitalWrite(A5,HIGH);
  }
  else{
    digitalWrite(A5,LOW);
  }

  delay(1000);        // delay in between reads for stability
}
