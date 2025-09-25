#include "TOFSensors.h"
#include <Arduino.h>

// Global distance variables
int distLeft = 2000;
int distCenter = 2000;
int distRight = 2000;

// Sensor objects
Adafruit_VL53L0X loxLeft = Adafruit_VL53L0X();
Adafruit_VL53L0X loxRight = Adafruit_VL53L0X();
Adafruit_VL53L0X loxCenter = Adafruit_VL53L0X();

bool initTOFSensors() {
  // Initialize I2C communication
  Wire.begin(I2C_SDA, I2C_SCL);

  // Configure shutdown pins
  pinMode(XSHUT_LEFT, OUTPUT);
  pinMode(XSHUT_RIGHT, OUTPUT);
  pinMode(XSHUT_CENTER, OUTPUT);

  // Reset all sensors
  digitalWrite(XSHUT_LEFT, LOW);
  digitalWrite(XSHUT_RIGHT, LOW);
  digitalWrite(XSHUT_CENTER, LOW);
  delay(100);

  // Initialize center sensor first
  digitalWrite(XSHUT_CENTER, HIGH);
  delay(150);
  if (!loxCenter.begin(ADDR_CENTER, &Wire)) {
    Serial.println("Failed to initialize center TOF sensor!");
    return false;
  }

  // Initialize left sensor
  digitalWrite(XSHUT_LEFT, HIGH);
  delay(150);
  if (!loxLeft.begin(ADDR_LEFT, &Wire)) {
    Serial.println("Failed to initialize left TOF sensor!");
    return false;
  }

  // Initialize right sensor
  digitalWrite(XSHUT_RIGHT, HIGH);
  delay(150);
  if (!loxRight.begin(ADDR_RIGHT, &Wire)) {
    Serial.println("Failed to initialize right TOF sensor!");
    return false;
  }

  Serial.println("All TOF sensors initialized successfully!");
  return true;
}

void readTOF() {
  VL53L0X_RangingMeasurementData_t measure;

  // Read left sensor
  loxLeft.rangingTest(&measure, false);
  distLeft = (measure.RangeStatus != 4) ? measure.RangeMilliMeter : 2000;

  // Read center sensor
  loxCenter.rangingTest(&measure, false);
  distCenter = (measure.RangeStatus != 4) ? measure.RangeMilliMeter : 2000;

  // Read right sensor
  loxRight.rangingTest(&measure, false);
  distRight = (measure.RangeStatus != 4) ? measure.RangeMilliMeter : 2000;

  // Apply constraints to filter invalid readings
  distLeft   = constrain(distLeft, 30, 2000);
  distCenter = constrain(distCenter, 25, 2000);
  distRight  = constrain(distRight, 30, 2000);
}

int getLeftDistance() {
  return distLeft;
}

int getCenterDistance() {
  return distCenter;
}

int getRightDistance() {
  return distRight;
}

bool isWallLeft(int threshold) {
  return distLeft < threshold;
}

bool isWallFront(int threshold) {
  return distCenter < threshold;
}

bool isWallRight(int threshold) {
  return distRight < threshold;
}