# Micromouse Robot - Ducks From Denmark

This repository contains the micromouse implementation for the team **Ducks From Denmark** for the IEEE micromouse competition. The ESP32-based micromouse robot code has been refactored into a professional, modular structure for better maintainability, readability, and development efficiency.

## 🎯 Competition Configuration

This micromouse is specifically configured for **350mm × 350mm maze cells** with a **100mm × 100mm mouse**.

### Key Competition Features

- **Large Cell Navigation**: Optimized for 350mm cells (3.5× larger than standard 100mm cells)
- **Empirically Tested Wheelbase**: 37mm wheelbase based on testing
- **Advanced PID Control**: Tuned for longer distance movements
- **Enhanced Wall Detection**: Thresholds optimized for larger cell distances
- **Optimized Speed Control**: Balanced for accuracy and speed in larger mazes

## 📁 File Structure

```
micromouse/
├── duck.ino              # Main program file (setup() and loop())
├── micromouse.ino        # Competition Arduino sketch
├── Config.h              # Configuration and constants
├── config.h              # Competition-specific configuration
├── MotorControl.h/.cpp   # Motor control module
├── Encoder.h/.cpp        # Encoder handling module
├── TOFSensors.h/.cpp     # Time-of-Flight sensor module
├── Movement.h/.cpp       # Robot movement functions
├── movement.h            # Motor control and movement functions
├── WallFollowing.h/.cpp  # Wall following algorithms
├── MazeNavigation.h/.cpp # Maze solving logic
├── sensors.h             # Wall detection and sensor management
├── pid.h                 # PID control algorithms
├── test.h                # Validation and testing functions
├── README_CONFIGURATION.md # Detailed parameter documentation
└── README.md            # This documentation
```

## 🔧 Module Descriptions

### 1. **Config.h / config.h**

Contains all configuration constants and pin definitions:

- Motor pin assignments
- Encoder pin assignments
- Robot physical specifications
- PID parameters
- Maze dimensions (350mm cells for competition)
- TOF sensor settings
- Movement parameters

### 2. **MotorControl Module**

Handles all motor operations:

- Individual motor control (left/right)
- Combined motor control
- Motor initialization
- Motor stopping functionality

### 3. **Encoder Module**

Manages encoder functionality:

- Quadrature encoder decoding
- Interrupt service routines
- Encoder count tracking and retrieval

### 4. **TOFSensors Module**

Handles Time-of-Flight sensor operations:

- Multiple sensor initialization and management
- Distance measurements
- Sensor calibration
- Wall detection logic optimized for 350mm cells

### 5. **Movement Module**

Core robot movement functions:

- Basic movement primitives (forward, turn, stop)
- Distance-based movement for large cells
- Encoder-based position tracking
- Speed control optimized for competition

### 6. **WallFollowing Module**

Wall following algorithms:

- Left-hand rule implementation
- Wall detection and tracking
- Corridor navigation
- Turn decision making

### 7. **MazeNavigation Module**

Advanced maze solving capabilities:

- Flood fill algorithm implementation
- Path planning and optimization
- Goal-seeking behavior
- Map representation and updates

## 🚀 Key Features

### Professional Code Structure
- **Modular Design**: Each component is separated into its own module
- **Clean Interfaces**: Well-defined function signatures and documentation
- **Maintainable**: Easy to modify, debug, and extend
- **Readable**: Clear naming conventions and code organization

### Competition-Ready Algorithms
- **Flood Fill**: Efficient maze solving algorithm
- **PID Control**: Smooth and accurate movement for large cells
- **Wall Following**: Reliable navigation in unknown environments
- **Sensor Fusion**: Multiple TOF sensors for robust wall detection

### Hardware Abstraction
- **Pin Configuration**: Centralized hardware configuration
- **Sensor Management**: Abstracted sensor interfaces
- **Motor Control**: Hardware-independent movement functions

## 📋 Usage Instructions

### 1. Hardware Setup

Ensure your ESP32 is connected according to the pin definitions in configuration files:

- Motors connected to designated PWM pins
- Encoders connected to interrupt-capable pins
- TOF sensors properly wired and addressed
- Power supply adequate for all components
- 37mm wheelbase for competition optimization

### 2. Software Upload

1. Open `duck.ino` or `micromouse.ino` in Arduino IDE
2. Select appropriate ESP32 board
3. Install required libraries (VL53L0X, etc.)
4. Upload to your ESP32

### 3. Competition Setup

1. Upload to Arduino-compatible microcontroller
2. Set `TEST_MODE = true` to validate configuration
3. Set `TEST_MODE = false` for maze operation
4. Calibrate sensors before competition
5. Verify 350mm cell distance calibration

### 4. Configuration

Modify configuration files to match your hardware:

```cpp
// Competition configuration
#define WHEEL_DIAMETER_MM 32.0
#define WHEELBASE_MM 37.0          // Competition-tested wheelbase
#define ENCODER_COUNTS_PER_REV 360
#define CELL_SIZE_MM 350.0         // Large competition cells
```

### 5. Testing

The code includes built-in testing functions:

1. **Motor Test**: Verify motor connections and directions
2. **Encoder Test**: Check encoder functionality
3. **Sensor Test**: Validate TOF sensor readings for 350mm distances
4. **Movement Test**: Test basic movement functions
5. **Cell Movement Test**: Verify accurate 350mm movements

### 6. Maze Solving

Competition-ready maze solving:

1. **Explore Phase**: Map the maze using wall following
2. **Solve Phase**: Use flood fill to find optimal path
3. **Speed Run**: Execute fastest path to center
4. **Large Cell Optimization**: Handle 350mm cell navigation

## ⚙️ Competition Parameters

### Movement Parameters
- `MOVE_SPEED`: Base movement speed
- `TURN_SPEED`: Turning speed  
- `CELL_DISTANCE_MM`: 350mm for competition cells

### PID Parameters (Tuned for Large Cells)
- `KP_LINEAR`: Proportional gain for straight movement
- `KI_LINEAR`: Integral gain for straight movement
- `KD_LINEAR`: Derivative gain for straight movement

### Sensor Parameters
- `WALL_THRESHOLD`: Distance threshold optimized for 350mm cells
- `SENSOR_TIMEOUT`: Maximum sensor reading time

## 🔧 Development Guidelines

### Adding New Features

1. Create new module files (.h/.cpp)
2. Follow the existing naming conventions
3. Add proper documentation
4. Update this README
5. Test with 350mm cell configuration

For detailed configuration information, see `README_CONFIGURATION.md`.

## 🏆 Team Information

**Team**: Ducks From Denmark  
**Competition**: IEEE Micromouse  
**Specialization**: 350mm × 350mm maze cells with 100mm × 100mm mouse

## 📝 Author

Ahmed El Shaboury - 2024

---

This modular structure transforms a single-file ESP32 program into a professional, maintainable codebase specifically optimized for IEEE micromouse competition with large 350mm cells.

## 📁 File Structure

```
micromouse/
├── duck.ino              # Main program file (setup() and loop())
├── Config.h              # Configuration and constants
├── MotorControl.h/.cpp   # Motor control module
├── Encoder.h/.cpp        # Encoder handling module
├── TOFSensors.h/.cpp     # Time-of-Flight sensor module
├── Movement.h/.cpp       # Robot movement functions
├── WallFollowing.h/.cpp  # Wall following algorithms
├── MazeNavigation.h/.cpp # Maze solving logic
└── README.md            # This documentation
```

## 🔧 Module Descriptions

### 1. **Config.h**

Contains all configuration constants and pin definitions:

- Motor pin assignments
- Encoder pin assignments
- Robot physical specifications
- PID parameters
- Maze dimensions
- TOF sensor settings
- Movement parameters

### 2. **MotorControl Module**

Handles all motor operations:

- Individual motor control (left/right)
- Combined motor control
- Motor initialization
- Motor stopping functionality

### 3. **Encoder Module**

Manages encoder functionality:

- Quadrature encoder decoding
- Interrupt service routines
- Encoder count tracking and retrieval
- Count reset functionality

### 4. **TOFSensors Module**

Manages VL53L0X Time-of-Flight sensors:

- Three sensor initialization (left, center, right)
- Distance reading and filtering
- Wall detection functions
- I2C address management

### 5. **Movement Module**

Provides robot movement primitives:

- Forward movement with distance control
- 90-degree turns (left/right)
- 180-degree turns
- Encoder-based movement feedback

### 6. **WallFollowing Module**

Implements wall following algorithms:

- PID-based wall following
- Left/right wall following
- Opening detection and handling
- Emergency stop functionality
- Configurable PID parameters

### 7. **MazeNavigation Module** ⭐ *FULLY IMPLEMENTED FLOOD FILL*

Contains complete maze solving logic:

- **Complete Flood Fill Algorithm**: Full implementation with dynamic updates
- **Wall Mapping System**: Tracks discovered walls with 4-directional mapping
- **Intelligent Navigation**: Chooses optimal path based on flood values
- **Goal Detection**: Handles goal reached behavior
- **Position Tracking**: Accurate position and direction management
- **Real-time Updates**: Recalculates flood fill when new walls discovered
- **Debugging Tools**: Visual maze and flood fill map printing

#### **Flood Fill Algorithm Features:**

- **Dynamic Wall Discovery**: Updates maze map as robot explores
- **Optimal Path Finding**: Always chooses the shortest known path to goal
- **Boundary Handling**: Properly handles maze boundaries
- **Queue-based Updates**: Efficient flood fill recalculation
- **Multi-goal Support**: Can handle different goal positions
- **Deadlock Prevention**: Handles situations with no accessible neighbors

## 🚀 Key Benefits of Modular Structure

### **Complete Flood Fill Implementation** 🧠

- **Intelligent Navigation**: Uses proper flood fill algorithm instead of simple right-hand rule
- **Dynamic Learning**: Updates maze map as walls are discovered
- **Optimal Pathfinding**: Always finds shortest known path to goal
- **Real-time Adaptation**: Recalculates routes when new obstacles found

### **Maintainability**

- Each module has a single responsibility
- Easy to locate and fix bugs
- Clear separation of concerns

### **Readability**

- Well-documented functions with Doxygen comments
- Logical organization of related functions
- Clean main file focusing only on high-level flow

### **Reusability**

- Modules can be reused in other projects
- Easy to test individual components
- Standardized interfaces between modules

### **Scalability**

- Easy to add new features or modules
- Simple to modify individual subsystems
- Professional software architecture

## 🔄 How It Works

### **Flood Fill Algorithm Flow:**

1. **Initialization**: Sets up maze with boundary walls and initial flood values
2. **Wall Scanning**: TOF sensors detect walls in current cell
3. **Map Update**: Discovered walls update the maze map
4. **Flood Fill Recalculation**: Algorithm recalculates optimal distances from all cells to goal
5. **Decision Making**: Robot chooses accessible neighbor with lowest flood value
6. **Movement Execution**: Robot turns and moves to selected cell
7. **Repeat**: Process continues until goal is reached

### **Main Program Flow:**

1. **Setup Phase**: `duck.ino` calls initialization functions from each module
2. **Main Loop**: Runs the flood fill navigation decision-making algorithm
3. **Module Interaction**: Modules communicate through well-defined interfaces

## 🧭 Navigation Algorithm Details

The robot now uses a **complete flood fill algorithm** that:

- Maintains a dynamic map of discovered walls
- Calculates shortest paths to the goal in real-time
- Adapts to newly discovered obstacles
- Guarantees optimal navigation (shortest path) to the goal

This is a significant improvement over simple wall-following algorithms!

## 🛠️ Compilation

All files should be placed in the same Arduino sketch folder. The Arduino IDE will automatically compile all `.cpp` files along with the main `.ino` file.

## 🔧 Configuration

To modify robot behavior:

1. **Hardware changes**: Update pin assignments in `Config.h`
2. **PID tuning**: Modify PID constants in `Config.h` or use `setPIDGains()`
3. **Movement parameters**: Adjust speeds and distances in `Config.h`
4. **Maze size**: Change `MAZE_ROWS` and `MAZE_COLS` in `Config.h`

## 📊 Testing

Uncomment the test sequence in `loop()` function to test individual movements:

- Forward movement
- Turning functions
- Sensor readings

## 🤝 Contributing

When adding new features:

1. Create appropriate header (.h) and implementation (.cpp) files
2. Follow the existing naming conventions
3. Add proper documentation
4. Update this README

---

This modular structure transforms a single-file ESP32 program into a professional, maintainable codebase suitable for complex robotics projects.
