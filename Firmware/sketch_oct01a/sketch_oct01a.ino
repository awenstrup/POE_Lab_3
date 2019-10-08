#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

  
void setup() {
  // put your setup code here, to run once:
  
  AFMS.begin();
  myMotor->setSpeed(150);
  myMotor2->setSpeed(150);
}

void loop() {
  // put your main code here, to run repeatedly:
  myMotor->run(BACKWARD);
  myMotor2->run(BACKWARD);

}
