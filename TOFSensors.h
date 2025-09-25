#ifndef TOF_SENSORS_H
#define TOF_SENSORS_H

#include "Config.h"
#include <Wire.h>
#include "Adafruit_VL53L0X.h"

/**
 * @brief TOF (Time of Flight) Sensors Module
 * 
 * This module handles all VL53L0X sensor operations including:
 * - Sensor initialization with different I2C addresses
 * - Distance reading from all three sensors
 * - Distance data filtering and constraining
 */

// Global distance variables (in millimeters)
extern int distLeft;
extern int distCenter; 
extern int distRight;

// Sensor objects
extern Adafruit_VL53L0X loxLeft;
extern Adafruit_VL53L0X loxRight;
extern Adafruit_VL53L0X loxCenter;

/**
 * @brief Initialize all TOF sensors
 * Sets up I2C communication and configures sensor addresses
 * Should be called in setup()
 * @return true if all sensors initialized successfully, false otherwise
 */
bool initTOFSensors();

/**
 * @brief Read distances from all TOF sensors
 * Updates global distance variables: distLeft, distCenter, distRight
 * Applies constraints to filter out invalid readings
 */
void readTOF();

/**
 * @brief Get the left sensor distance
 * @return Distance in millimeters
 */
int getLeftDistance();

/**
 * @brief Get the center sensor distance
 * @return Distance in millimeters
 */
int getCenterDistance();

/**
 * @brief Get the right sensor distance
 * @return Distance in millimeters
 */
int getRightDistance();

/**
 * @brief Check if there's a wall on the left
 * @param threshold Distance threshold in mm
 * @return true if wall detected, false otherwise
 */
bool isWallLeft(int threshold = OPENING_THRESHOLD);

/**
 * @brief Check if there's a wall in front
 * @param threshold Distance threshold in mm
 * @return true if wall detected, false otherwise
 */
bool isWallFront(int threshold = FRONT_WALL_THRESHOLD);

/**
 * @brief Check if there's a wall on the right
 * @param threshold Distance threshold in mm
 * @return true if wall detected, false otherwise
 */
bool isWallRight(int threshold = OPENING_THRESHOLD);

#endif // TOF_SENSORS_H