#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Config.h"

/**
 * @brief Movement Module
 * 
 * This module handles all robot movement operations including:
 * - Forward movement with distance control
 * - Turning operations (left, right, 180 degrees)
 * - Movement with encoder feedback
 */

/**
 * @brief Move robot forward by specified distance
 * Uses encoder feedback to control distance accurately
 * @param distance_mm Distance to move in millimeters
 */
void moveForwardMM(float distance_mm);

/**
 * @brief Turn robot left by 90 degrees
 * Uses encoder feedback for accurate turning
 */
void turnLeft90();

/**
 * @brief Turn robot right by 90 degrees
 * Uses encoder feedback for accurate turning
 */
void turnRight90();

/**
 * @brief Turn robot 180 degrees
 * Uses encoder feedback for accurate turning
 */
void turn180();

/**
 * @brief Move forward with wall following during movement
 * Combines forward movement with wall following PID control
 * @param distance_mm Distance to move in millimeters
 */
void moveForwardWithWallFollowing(float distance_mm);

#endif // MOVEMENT_H