#include "Encoder.h"
#include <Arduino.h>

// Ensure IRAM_ATTR is defined for non-ESP32 platforms
#ifndef IRAM_ATTR
  #define IRAM_ATTR
#endif

// Global encoder count variables
volatile long encoderCountLeft  = 0;
volatile long encoderCountRight = 0;

void initEncoders() {
  pinMode(ENCODER_LEFT_A, INPUT_PULLUP);
  pinMode(ENCODER_LEFT_B, INPUT_PULLUP);
  pinMode(ENCODER_RIGHT_A, INPUT_PULLUP);
  pinMode(ENCODER_RIGHT_B, INPUT_PULLUP);

  // Attach interrupts for quadrature decoding
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A), encoderISRLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_B), encoderISRLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A), encoderISRRight, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_B), encoderISRRight, CHANGE);
  
  // Reset encoder counts
  resetEncoders();
}

void IRAM_ATTR encoderISRLeft() {
  static uint8_t old_AB = 0;
  const int8_t enc_states[] = {0, -1, 1, 0, 1, 0, 0, -1,
                               -1, 0, 0, 1, 0, 1, -1, 0};
  old_AB <<= 2;
  old_AB |= (digitalRead(ENCODER_LEFT_A) << 1) | digitalRead(ENCODER_LEFT_B);
  encoderCountLeft += enc_states[(old_AB & 0x0F)];
}

void IRAM_ATTR encoderISRRight() {
  static uint8_t old_AB = 0;
  const int8_t enc_states[] = {0, -1, 1, 0, 1, 0, 0, -1,
                               -1, 0, 0, 1, 0, 1, -1, 0};
  old_AB <<= 2;
  old_AB |= (digitalRead(ENCODER_RIGHT_A) << 1) | digitalRead(ENCODER_RIGHT_B);
  encoderCountRight += enc_states[(old_AB & 0x0F)];
}

void resetEncoders() {
  encoderCountLeft = 0;
  encoderCountRight = 0;
}

long getLeftEncoderCount() {
  return encoderCountLeft;
}

long getRightEncoderCount() {
  return encoderCountRight;
}

long getAverageEncoderCount() {
  return (abs(encoderCountLeft) + abs(encoderCountRight)) / 2;
}