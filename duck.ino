/**
 * @file duck.ino
 * @brief Main micromouse control program
 * 
 * This is the main program file for the ESP32-based micromouse robot.
 * The code has been modularized into separate header and implementation files
 * for better organization and maintainability.
 * 
 * @author Ahmed El Shaboury
 * @date 2024
 */

// Include all necessary modules
#include "Config.h"
#include "MotorControl.h"
#include "Encoder.h"
#include "TOFSensors.h"
#include "Movement.h"
#include "WallFollowing.h"
#include "MazeNavigation.h"
#include <Arduino.h>

/**
 * @brief Arduino setup function
 * Initializes all robot subsystems
 */
void setup() {
  Serial.begin(115200);
  
  // Initialize LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  // Initialize additional input pins
  pinMode(23, INPUT);
  pinMode(4, INPUT);
  
  // Initialize all subsystems
  initMotors();
  initEncoders();
  
  // Initialize TOF sensors
  if (!initTOFSensors()) {
    Serial.println("Failed to initialize TOF sensors!");
    while (1); // Stop execution if sensors fail
  }
  
  // Initialize wall following and maze navigation
  initWallFollowing();
  initMazeNavigation();
  
  Serial.println("Robot Ready!");
  Serial.print("COUNTS_PER_MM: ");
  Serial.println(COUNTS_PER_MM);
  Serial.print("COUNTS_PER_90_DEG: ");
  Serial.println(COUNTS_PER_90_DEG);
}

/**
 * @brief Arduino main loop function
 * Runs the main maze solving algorithm
 */
void loop() {
  // Main maze solving loop
  decideAndMove();
  delay(100);
}