//Include requisite libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//Create motor and motor shield objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

//The point at which the sensor knows it is LEAVING the line
int leftSensorThreshold = 300;
int rightSensorThreshold = 300;

//The point at which the sensor knows it HAS LEFT the line
int leftSensorLow = 50;
int rightSensorLow = 50;

//Default speed for both motors
#define motorSpeed 15

//Amount to change motor speed by when turning
#define motorDelta 25

//State of the vehicle relative to the line
int state = 0;

//Define port numbers for IR sensors
#define leftSensor A1
#define rightSensor A0

int speedRight = 0;
int speedLeft = 0;

char mess[20] = "";

  
void setup() {
  //Open Serial Port
  Serial.begin(9600);
  //Wait to start
  delay(2000);
  
  //Initialize motor controller and motors
  AFMS.begin();
  leftMotor->setSpeed(motorSpeed);
  rightMotor->setSpeed(motorSpeed);

  //Enable debugging LED
  pinMode(13, OUTPUT);
}

void loop() {
  
  /*
   * Cases:
   * On the line: 0
   * Veering left : 1
   * Off to the left: 2
   * Veering right: 3
   * Off to the right: 4
   * Error: 5
   */

  digitalWrite(13, LOW);
  
  //Read IR sensors
  
  int l = analogRead(leftSensor);
  int r = analogRead(rightSensor);
//  sprintf(mess, "%d %d %d %d, l, r, speedL/eft, speedRight);
//  Serial.print(state);
//  Serial.print(" ");
//  Serial.print(l);
//  Serial.print(" ");
//  Serial.println(r);
  
  //On line
  if (l > leftSensorThreshold && r > rightSensorThreshold) {
    speedRight = motorSpeed;
    speedLeft = motorSpeed;
//    Serial.pri/nt(0);
  }
  
  //Veering left
  else if ((l < leftSensorThreshold && l > leftSensorLow) && r > rightSensorThreshold) {
    speedRight = motorSpeed;
    speedLeft = motorSpeed + motorDelta;
//    Serial.print(1);/
  }
  
  //Off left
  else if (l < leftSensorThreshold && r > rightSensorLow) {
    speedRight = motorSpeed-motorDelta;
    speedLeft = motorSpeed+motorDelta;
//    Serial.pr/int(2);
  }
  
  //Veering right
  else if (l > leftSensorThreshold && r > rightSensorLow && r < rightSensorThreshold) {
    speedRight = motorSpeed+motorDelta;
    speedLeft = motorSpeed;
//    Serial.prin/t(3);
  }
  
  //Off right
  else if (r < rightSensorThreshold && l > leftSensorLow ) {
    speedRight = motorSpeed+motorDelta;
    speedLeft = motorSpeed-motorDelta;
//    Serial.print(4/);
  }
  
  //Whoops!
  else {
    digitalWrite(13, HIGH);
    speedRight = 0;
    speedLeft = 0;
//    Serial.print(/5);
  }

  leftMotor->setSpeed(speedLeft > 0 ? speedLeft: -speedLeft);
  rightMotor->setSpeed(speedRight > 0 ? speedRight: -speedRight);
  leftMotor->run(speedLeft > 0 ? BACKWARD : FORWARD);
  rightMotor->run(speedRight > 0 ? BACKWARD : FORWARD);
  sprintf(mess, "  %d %d %d %d", l, r, speedLeft > 0 ? speedLeft: -speedLeft, speedRight > 0 ? speedRight: -speedRight);
  Serial.println(mess);
}
