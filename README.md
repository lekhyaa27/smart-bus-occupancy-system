# Smart Bus Occupancy and Passenger Counting System

## About the Project
A Smart Bus Occupancy System designed to monitor passenger movement and real-time seat availability using two infrared sensors.

The system identifies passenger entry and exit based on the sequence in which the sensors are triggered.

## Features
- Automatic passenger entry detection.
- Automatic passenger exit detection.
- Real-time passenger count.
- Total number of passengers boarded.
- Available seat monitoring.
- LCD-based digital display.

## Components Used
- Arduino UNO (board assumed; confirm actual board)
- Two IR sensors
- 16x2 LCD Display
- I2C LCD Module
- Connecting wires
- Breadboard

## Working Principle

Two IR sensors are placed at different positions on the bus staircase.

**Passenger Entry:**
Sensor 1 → Sensor 2

**Passenger Exit:**
Sensor 2 → Sensor 1

The Arduino detects the sensor sequence and updates the passenger count accordingly.

## Technology Used
- Embedded C/C++
- Arduino IDE
- IR Sensors
- I2C LCD

## Future Improvements
- GPS-based bus tracking.
- Mobile application for live seat availability.
- Cloud-based passenger monitoring.
- Multiple bus occupancy monitoring.

## Author
Lekhya Nali

GitHub: https://github.com/lekhyaa27