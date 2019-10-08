//Include requisite libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//Create motor and motor shield objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

//The point at which the sensor knows it is LEAVING the line
int leftSensorThreshold = 512;
int rightSensorThreshold = 512;

//The point at which the sensor knows it HAS LEFT the line
int leftSensorLow = 256;
int rightSensorLow = 256;

//Default speed for both motors
int motorSpeed = 50;

//Amount to change motor speed by when turning
int motorDelta = 30;

//State of the vehicle relative to the line
int state = 0;

//Define port numbers for IR sensors
#define leftSensor A0
#define rightSensor A1

  
void setup() {
  //Initialize motor controller and motors
  AFMS.begin();
  leftMotor->setSpeed(motorSpeed);
  rightMotor->setSpeed(motorSpeed);
}

void loop() {
  switch(state) {
  //If veering one direction, steer the other way
  case 0: driveStraight(); break;
  case 1: steerRight(); break;
  case 2: correctRight(); break;
  case 3: steerLeft(); break;
  case 4: correctLeft(); break;

  default: error();
  }
  
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
}

int checkCase() { //Determines the state of the vehicle relative to the line
  /*
   * Cases:
   * On the line: 0
   * Veering left : 1
   * Off to the left: 2
   * Veering right: 3
   * Off to the right: 4
   * Error: 5
   */
  
  //Read IR sensors
  int l = analogRead(leftSensor);
  int r = analogRead(rightSensor);
  
  //On line
  if (l > leftSensorThreshold && r > rightSensorThreshold) return 0;
  
  //Veering left
  if (l < leftSensorThreshold && l > leftSensorLow && r > rightSensorThreshold) return 1;
  
  //Off left
  if (l < leftSensorLow && (r > rightSensorThreshold || state == 1)) return 2;
  
  //Veering right
  if (l > leftSensorThreshold && r > rightSensorLow && r < rightSensorThreshold) return 3;
  
  //Off right
  if (r < rightSensorLow && (l > leftSensorThreshold || state == 3)) return 4;
  
  //Whoops!
  else return 5;
}

void driveStraight() {
  //Drive straight while both sensors are on the line
  while (state == 0) {
    leftMotor->setSpeed(motorSpeed);
    rightMotor->setSpeed(motorSpeed);
    state = checkCase();
  }
}

void steerRight() {
  //Steer right when veering left
  while (state == 1) {
    leftMotor->setSpeed(motorSpeed-motorDelta);
    rightMotor->setSpeed(motorSpeed+motorDelta);
    state = checkCase();
  }
}

void correctRight() {
  //Steer hard right when off the line to the left
  while (state == 2) {
    leftMotor->setSpeed(motorSpeed-motorDelta);
    rightMotor->setSpeed(motorSpeed);
    state = checkCase();
  }
}

void steerLeft() {
  //Steer left when veering right
  while (state == 3) {
    leftMotor->setSpeed(motorSpeed+motorDelta);
    rightMotor->setSpeed(motorSpeed-motorDelta);
    state = checkCase();
  }
}

void correctLeft() {
  //Steer hard left when off the line to the right
  while (state == 4) {
    leftMotor->setSpeed(motorSpeed-motorDelta);
    rightMotor->setSpeed(motorSpeed);
    state = checkCase();
  }
}

void error() {
  //Spin in place to indicate an error
  while (state = 5) {
    leftMotor->setSpeed(128);
    rightMotor->setSpeed(-128);
  }
}
