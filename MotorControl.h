#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "Config.h"

/**
 * @brief Motor Control Module
 * 
 * This module handles all motor control operations including:
 * - Individual motor control (left/right)
 * - Combined motor control
 * - Motor stopping functionality
 */

/**
 * @brief Set left motor speed and direction
 * @param speed Motor speed (-255 to 255, negative for reverse)
 */
void setMotorLeft(int speed);

/**
 * @brief Set right motor speed and direction
 * @param speed Motor speed (-255 to 255, negative for reverse)
 */
void setMotorRight(int speed);

/**
 * @brief Set both motors simultaneously
 * @param left Left motor speed (-255 to 255)
 * @param right Right motor speed (-255 to 255)
 */
void setMotors(int left, int right);

/**
 * @brief Stop both motors immediately
 */
void stopMotors();

/**
 * @brief Initialize motor control pins
 * Should be called in setup()
 */
void initMotors();

#endif // MOTOR_CONTROL_H