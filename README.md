# IGOR Tree Climber
## Introduction
This how-to guide shows the steps needed to program a tree clibing robot with two gecko inspired grippers and a flippong body.

## Table of Contents
1. [Hardware Requirements](#hardware-requirements)
2. [Software Requirements](#software-requirements)
3. [Circuit Diagram](#circuit-diagram)
4. [Code Explanation](#code-explanation)
5. [Usage Instructions](#usage-instructions)
6. [Contributing](#contributing)
7. [License](#license)

## Hardware Requirements
- Arduino Uno Rev 3
- 2 Micro Servos
- 4 Standard Parallax Servos
- Ultrasonic Sensor (HC-SR04)
- Breadboard and Jumper Wires
- 5V Power Supply for Servos

## Software Requirements
- Arduino IDE (with included Servo Library)

## Circuit Diagram
![Circuit Diagram](plainCircuit.png)

## Code Explanation
### Setup
The `setup()` function attaches the sensor and servo pins as well as setting all servos to 0&deg,.

### Loop
The `loop()` function is where climbing occurs, by reading the distance to the canopy through the ultrasonic sensor measurements, and following a process to climb up if the distance to the canopy is large, and down after the distance has been achieved. This loop strategically counts the steps (or flips) taken to reach the top, then reverses the process on the way down without the need for feedback from the sensor.

### Functions
- `flip()`: For climbing up, rotates the standard servos on the body to flip the bottom gripper to the top (if the bottom gripper is released). For climbing down, rotates the servos to flip the top gripper to the bottom (if the top gripper is released).
- `unflip()`: The opposite of `flip()` which accounts for the servos' limited range of motion, allowing the robot body to keep flipping upwards and downwards depending on which gripper is released.
- `releaseGrip(Servo theServo)`: Slowly releases the given gripper's grip.
- `grip(Servo theServo)`: Slwly tightens the gripper's grip.
- `printDistance()`: Measures and prints the distance from the ultrasonic sensor.

## How To Use
1. **Connect the Components**: Assemble the circuit as per the diagram. This involves creating two sets of positive and ground rails on the breadboard, one from the Arduino's 5V and ground pins, and the other straight from the 5V power supply. Connect the ground rails to prevent overcurrent. Use the Arduino rail to power the 2 Micro Servos and the Ultrasonic Sensor, and use the power supply rails to power the 4 Standard Servos. As for the digital pins, See the diagram or find them at the beginning of main.cpp.
2. **Upload the Code**:
    - Open the Arduino IDE.
    - Copy the provided code into the IDE.
    - Upload the code to the Arduino board.
3. **Power the Servos**: Ensure the servos are adequately powered as described above.
4. **Run the Project**: Manually attach the robot onto the base of a tree using the top and bottom grippers. It will climb if the distance to the canopy is greater than 50 cm, and descend if it reaches the top.
