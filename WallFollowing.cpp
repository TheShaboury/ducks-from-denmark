#include "WallFollowing.h"
#include "TOFSensors.h"
#include "MotorControl.h"
#include <Arduino.h>

// PID variables
float Kp = DEFAULT_KP;
float Ki = DEFAULT_KI;
float Kd = DEFAULT_KD;

float prevError = 0;
float integral = 0;
unsigned long lastTime = 0;

void initWallFollowing() {
  Kp = DEFAULT_KP;
  Ki = DEFAULT_KI;
  Kd = DEFAULT_KD;
  prevError = 0;
  integral = 0;
  lastTime = millis();
}

void followRightWall(int targetDistance) {
  unsigned long now = millis();
  float deltaTime = (now - lastTime) / 1000.0;
  lastTime = now;
  
  if (deltaTime < 0.001) deltaTime = 0.001;
  
  
  float error = getRightDistance() - targetDistance;
  
  // منطقة ميتة (Deadzone) مثل الدالة الأصلية
  float Deadzone = 10.0;
  if (abs(error) < Deadzone) {
    error = 0;
    integral = 0;
  }

  float proportional = error;
  integral += error * deltaTime;
  integral = constrain(integral, -100, 100);
  float derivative = (error - prevError) / deltaTime;
  prevError = error;
  
  float correction = -(Kp * proportional + Ki * integral + Kd * derivative);
  
  int baseSpeed = BASE_SPEED;
  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;
  
  // تقليل السرعة عند وجود جدار أمامي قريب
  if (getCenterDistance() < FRONT_WALL_THRESHOLD) {
    float reductionFactor = map(getCenterDistance(), 50, FRONT_WALL_THRESHOLD, 0.3, 0.8);
    leftSpeed = leftSpeed * reductionFactor;
    rightSpeed = rightSpeed * reductionFactor;
  }
  
  leftSpeed = constrain(leftSpeed, MIN_SPEED, MAX_SPEED);
  rightSpeed = constrain(rightSpeed, MIN_SPEED, MAX_SPEED);
  
  setMotors(leftSpeed, rightSpeed);
  
  Serial.print("RightWall PID | Target: ");
  Serial.print(targetDistance);
  Serial.print("mm | Actual: ");
  Serial.print(distRight);
  Serial.print("mm | Err: ");
  Serial.print(error);
  Serial.print(" | LSpd: ");
  Serial.print(leftSpeed);
  Serial.print(" | RSpd: ");
  Serial.println(rightSpeed);
}

void followLeftWall(int targetDistance) {
  unsigned long now = millis();
  float deltaTime = (now - lastTime) / 1000.0;
  lastTime = now;
  
  if (deltaTime < 0.001) deltaTime = 0.001;
  
  // حالة الفتحات - استخدام نفس مبدأ التصفير
  
  float error = getLeftDistance() - targetDistance;
  
  // منطقة ميتة (Deadzone) مثل الدالة الأصلية
  float Deadzone = 10.0;
  if (abs(error) < Deadzone) {
    error = 0;
    integral = 0;
  }

  float proportional = error;
  integral += error * deltaTime;
  integral = constrain(integral, -100, 100);
  float derivative = (error - prevError) / deltaTime;
  prevError = error;
  
  float correction = -(Kp * proportional + Ki * integral + Kd * derivative);

  int baseSpeed = BASE_SPEED;
  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;
  
  // تقليل السرعة عند وجود جدار أمامي قريب
  if (getCenterDistance() < FRONT_WALL_THRESHOLD) {
    float reductionFactor = map(getCenterDistance(), 50, FRONT_WALL_THRESHOLD, 0.3, 0.8);
    leftSpeed = leftSpeed * reductionFactor;
    rightSpeed = rightSpeed * reductionFactor;
  }
  
  leftSpeed = constrain(leftSpeed, MIN_SPEED, MAX_SPEED);
  rightSpeed = constrain(rightSpeed, MIN_SPEED, MAX_SPEED);
  
  setMotors(leftSpeed, rightSpeed);
  
  Serial.print("LeftWall PID | Target: ");
  Serial.print(targetDistance);
  Serial.print("mm | Actual: ");
  Serial.print(distLeft);
  Serial.print("mm | Err: ");
  Serial.print(error);
  Serial.print(" | LSpd: ");
  Serial.print(leftSpeed);
  Serial.print(" | RSpd: ");
  Serial.println(rightSpeed);
}

void emergencyStop() {
  stopMotors();
  delay(200);
  Serial.println("Emergency stop activated!");
}

void handleOpening() {
  if (!isWallRight() && !isWallLeft()) {
    // Both sides open - go straight
    setMotors(BASE_SPEED, BASE_SPEED);
    Serial.println("Both sides open - going straight");
  } 
  else if (!isWallRight()) {
    // Right opening - follow left wall
    followLeftWall(WALL_FOLLOW_DISTANCE);
    Serial.println("Right opening - following left wall at 55mm");
  } 
  else if (!isWallLeft()) {
    // Left opening - follow right wall
    followRightWall(WALL_FOLLOW_DISTANCE);
    Serial.println("Left opening - following right wall at 55mm");
  }
}

void wallFollowingPID() {
  unsigned long now = millis();
  float deltaTime = (now - lastTime) / 1000.0;
  lastTime = now;
  
  if (deltaTime < 0.001) deltaTime = 0.001;
  
  // Check for openings
  if (!isWallLeft() || !isWallRight()) {
    integral = 0;
    handleOpening();
    return;
  }
  
  // Calculate PID error (difference between left and right distances)
  float error = (getLeftDistance() - getRightDistance());
  float proportional = error;

  // Dead zone to prevent small oscillations
  const float deadZone = 10.0;
  if (abs(error) < deadZone) {
    error = 0;
    integral = 0;
  }

  // Integral term with windup protection
  integral += error * deltaTime;
  integral = constrain(integral, -100, 100);
  
  // Derivative term
  float derivative = (error - prevError) / deltaTime;
  prevError = error;
  
  // Calculate PID correction
  float correction = (Kp * proportional + Ki * integral + Kd * derivative);
  
  // Apply correction to base speed
  int baseSpeed = BASE_SPEED;
  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;
  
  // Constrain speeds
  leftSpeed = constrain(leftSpeed, MIN_SPEED, MAX_SPEED);
  rightSpeed = constrain(rightSpeed, MIN_SPEED, MAX_SPEED);
  
  // Reduce speed if front wall is close
  if (getCenterDistance() < FRONT_WALL_THRESHOLD) {
    float reductionFactor = map(getCenterDistance(), 50, FRONT_WALL_THRESHOLD, 0.3, 0.8);
    leftSpeed = leftSpeed * reductionFactor;
    rightSpeed = rightSpeed * reductionFactor;
  }
  
  setMotors(leftSpeed, rightSpeed);
  
  // Debug output
  Serial.print("L: "); Serial.print(getLeftDistance());
  Serial.print("mm | R: "); Serial.print(getRightDistance());
  Serial.print("mm | Err: "); Serial.print(error);
  Serial.print(" | LSpd: "); Serial.print(leftSpeed);
  Serial.print(" | RSpd: "); Serial.println(rightSpeed);
}

float getPIDError() {
  return prevError;
}

void resetPID() {
  prevError = 0;
  integral = 0;
  lastTime = millis();
}

void setPIDGains(float kp, float ki, float kd) {
  Kp = kp;
  Ki = ki;
  Kd = kd;
}