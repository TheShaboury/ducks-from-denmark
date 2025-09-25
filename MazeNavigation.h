#ifndef MAZE_NAVIGATION_H
#define MAZE_NAVIGATION_H

#include "Config.h"

/**
 * @brief Maze Navigation Module
 * 
 * This module handles all maze solving operations including:
 * - Flood fill algorithm implementation
 * - Goal detection and handling
 * - Navigation decision making
 * - Position tracking
 * - Direction management
 */

// Position and direction variables
extern int currentX, currentY;
extern int dir; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT

// Goal position
extern int goalX, goalY;
extern int startX, startY;

// Maze data structures
extern int flood[MAZE_ROWS][MAZE_COLS];
extern bool visited[MAZE_ROWS][MAZE_COLS];

// Wall mapping data structures
// Each cell has 4 walls: North(0), East(1), South(2), West(3)
extern bool walls[MAZE_ROWS][MAZE_COLS][4];
extern bool wallsDiscovered[MAZE_ROWS][MAZE_COLS][4];

/**
 * @brief Initialize maze navigation system
 * Sets up flood fill map and initial position
 */
void initMazeNavigation();

/**
 * @brief Initialize flood fill algorithm
 * Calculates Manhattan distances to goal
 */
void initFlood();

/**
 * @brief Update flood fill map based on discovered walls
 * @param x Current X position
 * @param y Current Y position
 */
void updateFlood(int x, int y);

/**
 * @brief Check if robot has reached the goal
 * Handles goal reached behavior
 */
void checkGoal();

/**
 * @brief Make navigation decision and execute movement
 * Uses flood fill algorithm and sensor data to decide next move
 */
void decideAndMove();

/**
 * @brief Make navigation decision using flood fill algorithm
 * Chooses the accessible neighbor cell with lowest flood value
 * @return Direction to move (0=UP, 1=RIGHT, 2=DOWN, 3=LEFT, -1=no move)
 */
int getNextDirection();

/**
 * @brief Scan current cell for walls using TOF sensors
 * Updates the wall mapping based on sensor readings
 */
void scanWalls();

/**
 * @brief Set wall in the maze map
 * @param x Cell X coordinate
 * @param y Cell Y coordinate
 * @param direction Wall direction (0=North, 1=East, 2=South, 3=West)
 * @param hasWall True if wall exists, false if no wall
 */
void setWall(int x, int y, int direction, bool hasWall);

/**
 * @brief Check if there's a wall in specific direction from cell
 * @param x Cell X coordinate
 * @param y Cell Y coordinate
 * @param direction Wall direction (0=North, 1=East, 2=South, 3=West)
 * @return True if wall exists, false otherwise
 */
bool hasWall(int x, int y, int direction);

/**
 * @brief Get accessible neighbors of a cell
 * @param x Cell X coordinate
 * @param y Cell Y coordinate
 * @param neighbors Array to store accessible neighbor directions
 * @return Number of accessible neighbors
 */
int getAccessibleNeighbors(int x, int y, int* neighbors);

/**
 * @brief Print current flood fill map for debugging
 */
void printFloodMap();

/**
 * @brief Print current wall map for debugging
 */
void printWallMap();

/**
 * @brief Update robot position based on current direction
 * @param direction Current facing direction (0=UP, 1=RIGHT, 2=DOWN, 3=LEFT)
 */
void updatePosition(int direction);

/**
 * @brief Set goal position
 * @param x Goal X coordinate
 * @param y Goal Y coordinate
 */
void setGoal(int x, int y);

/**
 * @brief Set starting position
 * @param x Start X coordinate
 * @param y Start Y coordinate
 */
void setStartPosition(int x, int y);

/**
 * @brief Get current position
 * @param x Pointer to store current X coordinate
 * @param y Pointer to store current Y coordinate
 */
void getCurrentPosition(int* x, int* y);

/**
 * @brief Get current direction
 * @return Current direction (0=UP, 1=RIGHT, 2=DOWN, 3=LEFT)
 */
int getCurrentDirection();

/**
 * @brief Reset visited cells array
 */
void resetVisited();

/**
 * @brief Mark current cell as visited
 */
void markCurrentCellVisited();

/**
 * @brief Check if current cell has been visited
 * @return true if visited, false otherwise
 */
bool isCurrentCellVisited();

#endif // MAZE_NAVIGATION_H