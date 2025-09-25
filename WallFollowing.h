#ifndef WALL_FOLLOWING_H
#define WALL_FOLLOWING_H

#include "Config.h"

/**
 * @brief Wall Following Module
 * 
 * This module handles all wall following operations including:
 * - PID-based wall following control
 * - Right wall following
 * - Left wall following
 * - Emergency stop functionality
 * - Opening detection and handling
 */

/**
 * @brief Initialize wall following PID controller
 * Sets up PID parameters and variables
 */
void initWallFollowing();

/**
 * @brief Main PID wall following function
 * Keeps robot centered between walls or follows a wall at target distance
 */
void wallFollowingPID();

/**
 * @brief Follow right wall at specified distance
 * @param targetDistance Target distance from right wall in mm
 */
void followRightWall(int targetDistance);

/**
 * @brief Follow left wall at specified distance
 * @param targetDistance Target distance from left wall in mm
 */
void followLeftWall(int targetDistance);

/**
 * @brief Handle emergency situations
 * Stops robot immediately when obstacle detected
 */
void emergencyStop();

/**
 * @brief Handle openings in walls
 * Decides behavior when openings are detected on sides
 */
void handleOpening();

/**
 * @brief Get current PID error value
 * @return Current PID error
 */
float getPIDError();

/**
 * @brief Reset PID controller
 * Clears integral and derivative terms
 */
void resetPID();

/**
 * @brief Set PID gains
 * @param kp Proportional gain
 * @param ki Integral gain  
 * @param kd Derivative gain
 */
void setPIDGains(float kp, float ki, float kd);

#endif // WALL_FOLLOWING_H