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
int dirRight = 0;
int dirLeft = 0;

  
void setup() {
  Serial.begin(9600);
  //Wait to start
  delay(2000);
  
  //Initialize motor controller and motors
  AFMS.begin();
  leftMotor->setSpeed(motorSpeed);
  rightMotor->setSpeed(motorSpeed);

  //Enable debugging LED
  pinMode(13, OUTPUT);

  //Open serial port
  /*
  long baudRate = 9600;
  Serial.begin(baudRate);
  */
}

void loop() {
//  switch(state) {
//  //If veering one direction, steer the other way
//  case 0: driveStraight(); break;
//  case 1: steerRight(); break;
//  case 2: correctRight(); break;
//  case 3: steerLeft(); break;
//  case 4: correctLeft(); break;
//
//  default: error();
//  }
  checkCase();
  

  /*TEST, NOT FUNCTIONAL
  leftMotor->setSpeed(motorSpeed);
  rightMotor->setSpeed(motorSpeed);
  */

  /*
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
  */
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

  digitalWrite(13, LOW);
  
  //Read IR sensors
  int l = analogRead(leftSensor);
  int r = analogRead(rightSensor);
  Serial.print(state);
  Serial.print(" ");
  Serial.print(l);
  Serial.print(" ");
  Serial.println(r);
  
  //On line
  if (l > leftSensorThreshold && r > rightSensorThreshold) {
    speedRight = motorSpeed;
    speedLeft = motorSpeed;
  }
  
  //Veering left
  else if ((l < leftSensorThreshold && l > leftSensorLow) && r > rightSensorThreshold) {
    speedRight = motorSpeed;
    speedLeft = motorSpeed + motorDelta;
  }
  
  //Off left
  else if (l < leftSensorThreshold && r > rightSensorLow) {
    speedRight = motorSpeed-motorDelta;
    speedLeft = motorSpeed+motorDelta;
  }
  
  //Veering right
  else if (l > leftSensorThreshold && r > rightSensorLow && r < rightSensorThreshold) {
    speedRight = motorSpeed+motorDelta;
    speedLeft = motorSpeed;
  }
  
  //Off right
  else if (r < rightSensorThreshold && l > leftSensorLow ) {
    speedRight = motorSpeed+motorDelta;
    speedLeft = motorSpeed-motorSpeed;
  }
  
  //Whoops!
  else {
    digitalWrite(13, HIGH);
    speedRight = 0;
    speedLeft = 0;
  }

  leftMotor->setSpeed(speedLeft > 0 ? speedLeft: -speedLeft);
  rightMotor->setSpeed(speedRight > 0 ? speedRight: -speedRight);
  leftMotor->run(speedLeft > 0 ? BACKWARD : FORWARD);
  rightMotor->run(speedRight > 0 ? BACKWARD : FORWARD);
}

//void driveStraight() {
//  //Drive straight while both sensors are on the line
//  while (state == 0) {
//    leftMotor->setSpeed(motorSpeed);
//    rightMotor->setSpeed(motorSpeed);
//    leftMotor->run(BACKWARD);
//    rightMotor->run(BACKWARD);
//    state = checkCase();
//  }
//}
//
//void steerRight() {
//  //Steer right when veering left
//  while (state == 1) {
//    leftMotor->setSpeed(motorSpeed);
//    rightMotor->setSpeed(motorSpeed+motorDelta);
//    leftMotor->run(BACKWARD);
//    rightMotor->run(BACKWARD);
//    state = checkCase();
//  }
//}
//
//void correctRight() {
//  //Steer hard right when off the line to the left
//  while (state == 2) {
//    leftMotor->setSpeed(motorSpeed-motorDelta);
//    rightMotor->setSpeed(motorSpeed+motorDelta);
//    leftMotor->run(BACKWARD);
//    rightMotor->run(BACKWARD);
//    state = checkCase();
//  }
//}
//
//void steerLeft() {
//  //Steer left when veering right
//  while (state == 3) {
//    leftMotor->setSpeed(motorSpeed+motorDelta);
//    rightMotor->setSpeed(motorSpeed);
//    leftMotor->run(BACKWARD);
//    rightMotor->run(BACKWARD);
//    state = checkCase();
//  }
//}
//
//void correctLeft() {
//  //Steer hard left when off the line to the right
//  while (state == 4) {
//    leftMotor->setSpeed(motorSpeed+motorDelta);
//    rightMotor->setSpeed(motorSpeed-motorDelta);
//    leftMotor->run(BACKWARD);
//    rightMotor->run(BACKWARD);
//    state = checkCase();
//  }
//}
//
//void error() {
//  //Spin in place to indicate an error
//  while (state == 5) {
//    digitalWrite(13, HIGH);
//    leftMotor->setSpeed(0);
//    rightMotor->setSpeed(0);
//    leftMotor->run(BACKWARD);
//    rightMotor->run(BACKWARD);
//    state = checkCase();
//    digitalWrite(13, LOW);
//  }
//  }
