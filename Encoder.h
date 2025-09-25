#ifndef ENCODER_H
#define ENCODER_H

#include "Config.h"
#include <Arduino.h>

// Ensure IRAM_ATTR is defined for non-ESP32 platforms
#ifndef IRAM_ATTR
  #define IRAM_ATTR
#endif

/**
 * @brief Encoder Module
 * 
 * This module handles all encoder-related functionality including:
 * - Encoder count tracking
 * - Interrupt service routines
 * - Encoder initialization
 * - Count retrieval and reset functions
 */

// Global encoder count variables
extern volatile long encoderCountLeft;
extern volatile long encoderCountRight;

/**
 * @brief Initialize encoder pins and interrupts
 * Should be called in setup()
 */
void initEncoders();

/**
 * @brief Interrupt Service Routine for left encoder
 * Handles quadrature decoding for left wheel encoder
 */
void IRAM_ATTR encoderISRLeft();

/**
 * @brief Interrupt Service Routine for right encoder
 * Handles quadrature decoding for right wheel encoder
 */
void IRAM_ATTR encoderISRRight();

/**
 * @brief Reset both encoder counts to zero
 */
void resetEncoders();

/**
 * @brief Get the current left encoder count
 * @return Current left encoder count
 */
long getLeftEncoderCount();

/**
 * @brief Get the current right encoder count
 * @return Current right encoder count
 */
long getRightEncoderCount();

/**
 * @brief Get the average of both encoder counts
 * @return Average encoder count
 */
long getAverageEncoderCount();

#endif // ENCODER_H