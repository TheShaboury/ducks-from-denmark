#include "Movement.h"
#include "Encoder.h"
#include "MotorControl.h"
#include "TOFSensors.h"
#include "WallFollowing.h"
#include <Arduino.h>

void moveForwardMM(float distance_mm) {
  long targetCounts = 1.02 * distance_mm * COUNTS_PER_MM;
  resetEncoders();
  resetPID();
  Serial.print("Moving forward ");
  Serial.print(distance_mm);
  Serial.print("mm (Target counts: ");
  Serial.print(targetCounts);
  Serial.println(")");

  while (getAverageEncoderCount() < targetCounts) {
    readTOF();
    
    // Emergency stop if front wall too close
    if (getCenterDistance() <= EMERGENCY_DISTANCE) { 
      stopMotors(); 
      Serial.println("Emergency stop - front wall detected!");
      return; 
    }
    
    // Use wall following PID during movement
    wallFollowingPID();
    
    Serial.print("LeftEnc: ");
    Serial.print(getLeftEncoderCount());
    Serial.print(" | RightEnc: ");
    Serial.println(getRightEncoderCount());
    
    //delay(5);
  }
  
  stopMotors();
  Serial.println("Forward movement completed");
}

void moveForwardWithWallFollowing(float distance_mm) {
  // This is essentially the same as moveForwardMM since it already includes wall following
  moveForwardMM(distance_mm);
}

void turnLeft90() {
  resetEncoders();
  
  Serial.print("Turning left 90° (Target counts: ");
  Serial.print(COUNTS_PER_90_DEG);
  Serial.println(")");

  while (getAverageEncoderCount() < 1.12 * COUNTS_PER_90_DEG) {
    setMotors(-TURN_SPEED, TURN_SPEED);
    
    Serial.print("Left: ");
    Serial.print(getLeftEncoderCount());
    Serial.print(" | Right: ");
    Serial.println(getRightEncoderCount());
    
    delay(10);
  }
  
  stopMotors();
  Serial.println("Left turn completed");
}

void turnRight90() {
  resetEncoders();
  
  Serial.print("Turning right 90° (Target counts: ");
  Serial.print(COUNTS_PER_90_DEG);
  Serial.println(")");

  while (getAverageEncoderCount() < 1.12 * COUNTS_PER_90_DEG) {
    setMotors(TURN_SPEED, -TURN_SPEED);
    
    Serial.print("Left: ");
    Serial.print(getLeftEncoderCount());
    Serial.print(" | Right: ");
    Serial.println(getRightEncoderCount());
    
    delay(10);
  }
  
  stopMotors();
  Serial.println("Right turn completed");
}

void turn180() {
  resetEncoders();
  
  Serial.print("Turning 180° (Target counts: ");
  Serial.print(2 * COUNTS_PER_90_DEG);
  Serial.println(")");

  while (getAverageEncoderCount() < (1.25 * 2 * COUNTS_PER_90_DEG)) {
    setMotors(-TURN_SPEED, TURN_SPEED);
    
    Serial.print("Left: ");
    Serial.print(getLeftEncoderCount());
    Serial.print(" | Right: ");
    Serial.println(getRightEncoderCount());
    
    delay(10);
  }
  
  stopMotors();
  delay(50);
  // Additional backward movement for fine adjustment
  setMotors(-TURN_SPEED, -TURN_SPEED);
  delay(400);
  stopMotors();
  delay(50);
  
  Serial.println("180° turn completed");
}