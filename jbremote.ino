/*
 ProgramName:  jbremote
 Author:       Bobby Kawamura
 Date:         6/21/2014
 
 Remote volume control for a jukebox.
 A stepper motor is used to turn the exising volume control knob.
 An RF reciver and a key chain transmitter are used for a human interface.
 The arduino control the hardware.
 A motor control shield is used to interface with the stepper motor.
 Features a control for the reject button.
 
 Hardware used is an XL-R02 RF module 
 with signals from the four button key remote.
 Reads a digital input on pins 2-6, prints the result 
 to the serial monitor. Irt is based on the PT 2272 chip.
 The application uses the analog pins 
 since some shields use the digital pins.
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

// Use the basic motor control library
#include <AFMotor.h>
int Clinc = 15;
int Motorclutch = Clinc;
int lastpressed = 0;
// Connect a stepper motor with 200 steps per revolution
// to motor port #1.
AF_Stepper motor(200, 1);
// Pin 2 has an LED connected.
#define led 2

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
  pinMode(led, OUTPUT); 
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  digitalWrite(A4,HIGH);
  digitalWrite(A5,LOW);
  motor.setSpeed(30);   
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
  lastpressed = 0;
  if ( buttonB == 1 )
  {
    motor.step(1, FORWARD, INTERLEAVE);
    lastpressed = 1;
    Motorclutch = Motorclutch -1;
    digitalWrite(led, HIGH);   // turn the LED on 
    Serial.print("Forward\n");
  }
  if ( buttonA == 1 )
  {
    motor.step(1, BACKWARD, INTERLEAVE);
    lastpressed = 1; 
    Motorclutch  = Motorclutch - 1;
    digitalWrite(led, HIGH);   // turn the LED on
    Serial.print("Backward\n");
  }
  if ( lastpressed == 0 ) 
  {
    motor.release(); // stop rotation and turn off holding torque.
    Motorclutch =  Clinc;    // reset the clutch interval
    digitalWrite(led, LOW);    // turn the LED off   
  }
  if( Motorclutch == 0 )
  {
    motor.release(); // stop rotation and turn off holding torque.
    Motorclutch =  Clinc;    // reset the clutch interval
    digitalWrite(led, LOW);   // turn the LED off
    Serial.print("clutch release\n");
  }     
  // Set the relay on if button is pressed
  // rRelease the relay if not pressed.
  if ( buttonC == 1 )
  {
    digitalWrite(A5,HIGH);    // turn the LED on
    digitalWrite(led, HIGH);   // turn the LED on
    delay(1000);    //1 sec for JB tp latch
  }
  else{
    digitalWrite(A5,LOW);
  }
  delay(50);        // delay in between reads for stability
}

