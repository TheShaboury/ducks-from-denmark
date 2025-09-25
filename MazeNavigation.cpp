#include "MazeNavigation.h"
#include "TOFSensors.h"
#include "Movement.h"
#include "MotorControl.h"
#include <Arduino.h>

// Position and direction variables
int currentX = 0, currentY = 0;
int dir = 0; // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT

// Goal and start positions
int goalX = 8;
int goalY = 8;
int startX = 0;
int startY = 0;

// Maze data structures
int flood[MAZE_ROWS][MAZE_COLS];
bool visited[MAZE_ROWS][MAZE_COLS];

// Wall mapping data structures
// Each cell has 4 walls: North(0), East(1), South(2), West(3)
bool walls[MAZE_ROWS][MAZE_COLS][4];
bool wallsDiscovered[MAZE_ROWS][MAZE_COLS][4];

// Direction mappings for easier calculation
const int dx[] = {0, 1, 0, -1}; // North, East, South, West
const int dy[] = {1, 0, -1, 0};
const char* dirNames[] = {"North", "East", "South", "West"};

void initMazeNavigation() {
  // Initialize position
  currentX = startX;
  currentY = startY;
  dir = 0; // Start facing UP
  
  // Initialize wall mapping - assume no walls initially
  for(int r = 0; r < MAZE_ROWS; r++) {
    for(int c = 0; c < MAZE_COLS; c++) {
      for(int d = 0; d < 4; d++) {
        walls[r][c][d] = false;
        wallsDiscovered[r][c][d] = false;
      }
    }
  }
  
  // Add boundary walls
  for(int r = 0; r < MAZE_ROWS; r++) {
    for(int c = 0; c < MAZE_COLS; c++) {
      if(r == 0) setWall(c, r, 2, true);           // South wall for bottom row
      if(r == MAZE_ROWS-1) setWall(c, r, 0, true); // North wall for top row
      if(c == 0) setWall(c, r, 3, true);           // West wall for left column
      if(c == MAZE_COLS-1) setWall(c, r, 1, true); // East wall for right column
    }
  }
  
  // Initialize flood fill
  initFlood();
  
  // Reset visited array
  resetVisited();
  
  Serial.println("Maze navigation initialized");
  Serial.print("Start position: (");
  Serial.print(startX);
  Serial.print(", ");
  Serial.print(startY);
  Serial.println(")");
  Serial.print("Goal position: (");
  Serial.print(goalX);
  Serial.print(", ");
  Serial.print(goalY);
  Serial.println(")");
}

void initFlood() {
  // Calculate Manhattan distance to goal for each cell
  for(int r = 0; r < MAZE_ROWS; r++) {
    for(int c = 0; c < MAZE_COLS; c++) {
      flood[r][c] = abs(r - goalY) + abs(c - goalX);
    }
  }
  Serial.println("Flood fill map initialized");
}

void updateFlood(int x, int y) {
  // Recalculate flood fill values based on discovered walls
  // Use a queue-based flood fill algorithm
  
  // Initialize all cells to high value except goal
  for(int r = 0; r < MAZE_ROWS; r++) {
    for(int c = 0; c < MAZE_COLS; c++) {
      flood[r][c] = 999;
    }
  }
  
  // Set goal to 0
  flood[goalY][goalX] = 0;
  
  // Simple queue implementation using arrays
  int queueX[MAZE_ROWS * MAZE_COLS];
  int queueY[MAZE_ROWS * MAZE_COLS];
  int front = 0, rear = 0;
  
  // Add goal to queue
  queueX[rear] = goalX;
  queueY[rear] = goalY;
  rear++;
  
  // Process queue
  while(front < rear) {
    int currX = queueX[front];
    int currY = queueY[front];
    front++;
    
    int currentDistance = flood[currY][currX];
    
    // Check all 4 directions
    for(int d = 0; d < 4; d++) {
      int newX = currX + dx[d];
      int newY = currY + dy[d];
      
      // Check bounds
      if(newX >= 0 && newX < MAZE_COLS && newY >= 0 && newY < MAZE_ROWS) {
        // Check if there's no wall between current and new cell
        if(!hasWall(currX, currY, d)) {
          int newDistance = currentDistance + 1;
          
          // If we found a shorter path
          if(newDistance < flood[newY][newX]) {
            flood[newY][newX] = newDistance;
            
            // Add to queue for further processing
            queueX[rear] = newX;
            queueY[rear] = newY;
            rear++;
          }
        }
      }
    }
  }
  
  Serial.println("Flood fill map updated");
}

void checkGoal() {
  if (currentX == goalX && currentY == goalY) {
    stopMotors();
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("🎯 Goal Reached!");
    Serial.print("Final position: (");
    Serial.print(currentX);
    Serial.print(", ");
    Serial.print(currentY);
    Serial.println(")");
    
    // Goal reached - stop execution
    while (true) {
      delay(1000);
    }
  }
}

void decideAndMove() {
  // Scan walls in current cell
  scanWalls();
  
  // Update flood fill based on discovered walls
  updateFlood(currentX, currentY);
  
  // Mark current cell as visited
  markCurrentCellVisited();

  // Get next direction using flood fill algorithm
  int nextDir = getNextDirection();
  
  if(nextDir == -1) {
    Serial.println("No accessible neighbors - stuck!");
    return;
  }
  
  // Calculate required turns
  int turnDiff = (nextDir - dir + 4) % 4;
  
  // Execute turns
  if(turnDiff == 1) {
    // Turn right
    turnRight90();
    Serial.println("Turned right");
  }
  else if(turnDiff == 2) {
    // Turn around
    turn180();
    Serial.println("Turned around");
  }
  else if(turnDiff == 3) {
    // Turn left
    turnLeft90();
    Serial.println("Turned left");
  }
  // turnDiff == 0 means go straight (no turn needed)
  
  // Update current direction
  dir = nextDir;
  
  // Move forward one cell
  moveForwardMM(CELL_SIZE_MM);
  updatePosition(dir);
  
  Serial.print("Moved to Cell (");
  Serial.print(currentX);
  Serial.print(", ");
  Serial.print(currentY);
  Serial.print(") facing direction ");
  Serial.print(dir);
  Serial.print(" (");
  Serial.print(dirNames[dir]);
  Serial.print("), flood value: ");
  Serial.println(flood[currentY][currentX]);

  checkGoal();
}

void updatePosition(int direction) {
  if (direction == 0) currentY++;      // UP
  else if (direction == 1) currentX++; // RIGHT
  else if (direction == 2) currentY--; // DOWN    
  else if (direction == 3) currentX--; // LEFT
  
  // Ensure position stays within maze bounds
  currentX = constrain(currentX, 0, MAZE_COLS - 1);
  currentY = constrain(currentY, 0, MAZE_ROWS - 1);
}

void setGoal(int x, int y) {
  goalX = constrain(x, 0, MAZE_COLS - 1);
  goalY = constrain(y, 0, MAZE_ROWS - 1);
  
  Serial.print("Goal set to: (");
  Serial.print(goalX);
  Serial.print(", ");
  Serial.print(goalY);
  Serial.println(")");
}

void setStartPosition(int x, int y) {
  startX = constrain(x, 0, MAZE_COLS - 1);
  startY = constrain(y, 0, MAZE_ROWS - 1);
  currentX = startX;
  currentY = startY;
  
  Serial.print("Start position set to: (");
  Serial.print(startX);
  Serial.print(", ");
  Serial.print(startY);
  Serial.println(")");
}

void getCurrentPosition(int* x, int* y) {
  *x = currentX;
  *y = currentY;
}

int getCurrentDirection() {
  return dir;
}

void resetVisited() {
  for(int r = 0; r < MAZE_ROWS; r++) {
    for(int c = 0; c < MAZE_COLS; c++) {
      visited[r][c] = false;
    }
  }
}

void markCurrentCellVisited() {
  if (currentX >= 0 && currentX < MAZE_COLS && 
      currentY >= 0 && currentY < MAZE_ROWS) {
    visited[currentY][currentX] = true;
  }
}

bool isCurrentCellVisited() {
  if (currentX >= 0 && currentX < MAZE_COLS && 
      currentY >= 0 && currentY < MAZE_ROWS) {
    return visited[currentY][currentX];
  }
  return false;
}

int getNextDirection() {
  // Get accessible neighbors and their flood values
  int neighbors[4];
  int numNeighbors = getAccessibleNeighbors(currentX, currentY, neighbors);
  
  if(numNeighbors == 0) {
    return -1; // No accessible neighbors
  }
  
  // Find neighbor with lowest flood value
  int bestDir = neighbors[0];
  int bestFlood = 999;
  
  for(int i = 0; i < numNeighbors; i++) {
    int neighborDir = neighbors[i];
    int neighborX = currentX + dx[neighborDir];
    int neighborY = currentY + dy[neighborDir];
    
    int neighborFlood = flood[neighborY][neighborX];
    
    if(neighborFlood < bestFlood) {
      bestFlood = neighborFlood;
      bestDir = neighborDir;
    }
  }
  
  return bestDir;
}

void scanWalls() {
  readTOF();
  
  // Convert robot's relative directions to absolute maze directions
  int frontDir = dir;
  int rightDir = (dir + 1) % 4;
  int leftDir = (dir + 3) % 4;
  
  // Check front wall
  bool frontWall = isWallFront(130); // 120mm threshold for wall detection
  setWall(currentX, currentY, frontDir, frontWall);
  
  // Check right wall  
  bool rightWall = isWallRight(130); // 80mm threshold for side walls
  setWall(currentX, currentY, rightDir, rightWall);
  
  // Check left wall
  bool leftWall = isWallLeft(130); // 80mm threshold for side walls
  setWall(currentX, currentY, leftDir, leftWall);
  
  Serial.print("Scanned walls at (");
  Serial.print(currentX);
  Serial.print(", ");
  Serial.print(currentY);
  Serial.print("): Front=");
  Serial.print(frontWall ? "YES" : "NO");
  Serial.print(", Right=");
  Serial.print(rightWall ? "YES" : "NO");
  Serial.print(", Left=");
  Serial.println(leftWall ? "YES" : "NO");
}

void setWall(int x, int y, int direction, bool hasWallValue) {
  // Check bounds
  if(x < 0 || x >= MAZE_COLS || y < 0 || y >= MAZE_ROWS || direction < 0 || direction >= 4) {
    return;
  }
  
  // Set wall for current cell
  walls[y][x][direction] = hasWallValue;
  wallsDiscovered[y][x][direction] = true;
  
  // Set corresponding wall for adjacent cell
  int adjX = x + dx[direction];
  int adjY = y + dy[direction];
  int oppositeDir = (direction + 2) % 4;
  
  if(adjX >= 0 && adjX < MAZE_COLS && adjY >= 0 && adjY < MAZE_ROWS) {
    walls[adjY][adjX][oppositeDir] = hasWallValue;
    wallsDiscovered[adjY][adjX][oppositeDir] = true;
  }
}

bool hasWall(int x, int y, int direction) {
  // Check bounds
  if(x < 0 || x >= MAZE_COLS || y < 0 || y >= MAZE_ROWS || direction < 0 || direction >= 4) {
    return true; // Assume wall at boundaries
  }
  
  return walls[y][x][direction];
}

int getAccessibleNeighbors(int x, int y, int* neighbors) {
  int count = 0;
  
  for(int d = 0; d < 4; d++) {
    int newX = x + dx[d];
    int newY = y + dy[d];
    
    // Check bounds
    if(newX >= 0 && newX < MAZE_COLS && newY >= 0 && newY < MAZE_ROWS) {
      // Check if there's no wall in this direction
      if(!hasWall(x, y, d)) {
        neighbors[count++] = d;
      }
    }
  }
  
  return count;
}

void printFloodMap() {
  Serial.println("=== FLOOD FILL MAP ===");
  Serial.print("Goal: (");
  Serial.print(goalX);
  Serial.print(", ");
  Serial.print(goalY);
  Serial.println(")");
  
  for(int r = MAZE_ROWS - 1; r >= 0; r--) {
    for(int c = 0; c < MAZE_COLS; c++) {
      if(c == currentX && r == currentY) {
        Serial.print(" R ");
      } else if(c == goalX && r == goalY) {
        Serial.print(" G ");
      } else {
        Serial.print(" ");
        if(flood[r][c] < 10) Serial.print("0");
        Serial.print(flood[r][c]);
      }
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println("======================");
}

void printWallMap() {
  Serial.println("=== WALL MAP ===");
  for(int r = MAZE_ROWS - 1; r >= 0; r--) {
    // Print top walls
    for(int c = 0; c < MAZE_COLS; c++) {
      Serial.print("+");
      Serial.print(hasWall(c, r, 0) ? "---" : "   ");
    }
    Serial.println("+");
    
    // Print side walls and cells
    for(int c = 0; c < MAZE_COLS; c++) {
      Serial.print(hasWall(c, r, 3) ? "|" : " ");
      if(c == currentX && r == currentY) {
        Serial.print(" R ");
      } else if(c == goalX && r == goalY) {
        Serial.print(" G ");
      } else {
        Serial.print("   ");
      }
    }
    Serial.println(hasWall(MAZE_COLS-1, r, 1) ? "|" : " ");
  }
  
  // Print bottom walls
  for(int c = 0; c < MAZE_COLS; c++) {
    Serial.print("+");
    Serial.print(hasWall(c, 0, 2) ? "---" : "   ");
  }
  Serial.println("+");
  Serial.println("================");
}