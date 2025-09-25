#ifndef CONFIG_H
#define CONFIG_H

// ================== Motor Pin Configuration ==================
const int LEFT_MOTOR_PIN1  = 14;  
const int LEFT_MOTOR_PIN2  = 27;  
const int RIGHT_MOTOR_PIN1 = 12; 
const int RIGHT_MOTOR_PIN2 = 13; 

// ================== Encoder Pin Configuration ==================
const int ENCODER_LEFT_A  = 32;
const int ENCODER_LEFT_B  = 33;
const int ENCODER_RIGHT_A = 34;
const int ENCODER_RIGHT_B = 35;

// ================== Robot Physical Specifications ==================
const int ENCODER_PPR   = 7;    
const int GEAR_RATIO    = 82;  
const float WHEEL_DIAM  = 40.0; // mm
const float WHEEL_CIRC  = 3.14159 * WHEEL_DIAM;
const float COUNTS_PER_REV = 4.0 * ENCODER_PPR * GEAR_RATIO; // quadrature ×4
const float COUNTS_PER_MM  = COUNTS_PER_REV / WHEEL_CIRC;
const float WHEEL_BASE = 90.0; // mm
const float TURN_CIRC  = 3.14159 * WHEEL_BASE;
const long COUNTS_PER_90_DEG = (TURN_CIRC / 4.0) * COUNTS_PER_MM;

// ================== PID Control Parameters ==================
const float DEFAULT_KP = 1.4;   // Proportional gain
const float DEFAULT_KI = 0.08;  // Integral gain  
const float DEFAULT_KD = 1.1;   // Derivative gain

// ================== Maze Configuration ==================
const int MAZE_ROWS = 16;
const int MAZE_COLS = 16;
const int CELL_SIZE_MM = 180;   

// ================== TOF Sensor Configuration ==================
#define I2C_SDA 21
#define I2C_SCL 22
#define XSHUT_LEFT   5
#define XSHUT_RIGHT  19
#define XSHUT_CENTER 18
#define ADDR_LEFT   0x30
#define ADDR_RIGHT  0x31
#define ADDR_CENTER 0x32

// ================== Movement Parameters ==================
const int BASE_SPEED = 140;
const int MIN_SPEED = 60;
const int MAX_SPEED = 255;
const int TURN_SPEED = 80;

// ================== Distance Thresholds ==================
const int WALL_FOLLOW_DISTANCE = 55;
const int OPENING_THRESHOLD = 130;
const int EMERGENCY_DISTANCE = 25;
const int FRONT_WALL_THRESHOLD = 130;

// ================== LED Pin ==================
#define LED_BUILTIN 2

#endif // CONFIG_H