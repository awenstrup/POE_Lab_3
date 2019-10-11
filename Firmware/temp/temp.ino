int a = 0;
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);


void setup() {
  // put your setup code here, to run once:
  long baudRate = 9600;
  Serial.begin(baudRate);

  AFMS.begin();
  leftMotor->setSpeed(0);
  rightMotor->setSpeed(0);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int l = analogRead(A0);
  int r = analogRead(A1);

  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);

  Serial.println("Left");
  Serial.println(l);
  Serial.println("Right");
  Serial.println(r);
  Serial.println();

  delay(1000);
}
