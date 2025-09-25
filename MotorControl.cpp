#include "MotorControl.h"
#include <Arduino.h>

void initMotors() {
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  
  // Initialize motors to stopped state
  stopMotors();
}

void setMotorLeft(int speed) {
  speed = constrain(speed, -255, 255);
  if (speed >= 0) {
    analogWrite(LEFT_MOTOR_PIN1, speed);
    analogWrite(LEFT_MOTOR_PIN2, 0);
  } else {
    analogWrite(LEFT_MOTOR_PIN1, 0);
    analogWrite(LEFT_MOTOR_PIN2, -speed);
  }
}

void setMotorRight(int speed) {
  speed = constrain(speed, -255, 255);
  if (speed >= 0) {
    analogWrite(RIGHT_MOTOR_PIN1, speed);
    analogWrite(RIGHT_MOTOR_PIN2, 0);
  } else {
    analogWrite(RIGHT_MOTOR_PIN1, 0);
    analogWrite(RIGHT_MOTOR_PIN2, -speed);
  }
}

void setMotors(int left, int right) {
  setMotorLeft(left);
  setMotorRight(right);
}

void stopMotors() {
  setMotors(0, 0);
}