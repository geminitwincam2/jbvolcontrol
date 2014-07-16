// Uses Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
int i=1;
int dir = FORWARD;
// Connect a stepper motor with 200 steps per revolution
// to motor port #2 (M1 and M2)
AF_Stepper motor(200, 1);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");
  motor.setSpeed(30);  // rpm   
}

void loop() {
  // Rotate motor n steps clockwaie and reverse the direction
  // over and over.
  if ( i < 200) {
    motor.step(1, dir, INTERLEAVE); 
    i=i+1;
    delay( 100 );
  }
  else
  {
    i=1;
    dir=-dir;
  }
}
