#include <Servo.h>

// Micro Servos
Servo topGrip;
Servo bottomGrip;

// Parallax Servos
Servo first;  // Top Gripper Tilt
Servo second; // Closest to Top Gripper
Servo third;  // Closest to Bottom Gripper
Servo fourth; // Bottom Gripper Tilt

// Pins
const int topGripPin = 2;    // D2
const int bottomGripPin = 3; // D3

// Ultrasonic Pins
const int echoPin = 8; // D8
const int trigPin = 9;  // D9

const int firstPin = 10;  // D10
const int secondPin = 11; // etc.
const int thirdPin = 12;
const int fourthPin = 13;

int motorConfig = 0; // linked motors currently at 0 degrees (method because servos 180 only)
int reachedTop = 0; // hasn't reached top yet
int count = 0; // how many flips

// Variables for ultrasonic sensor
long duration;
float distance;

void setup() {
  // Setting up Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  // Setting up Motors
  topGrip.attach(topGripPin);
  bottomGrip.attach(bottomGripPin);
  first.attach(firstPin);
  second.attach(secondPin);
  third.attach(thirdPin);
  fourth.attach(fourthPin);

  // Motor Configuration at Base, every servo to 0 degrees
  grip(topGrip); 
  grip(bottomGrip);
  first.write(0);
  second.write(0);
  third.write(0);
  fourth.write(0);
}

void loop() {
  // Get Ultrasonic Distance
  printDistance();
  if (distance > 50) {
    // body not yet at top so must climb up
    // Check which configuration the body is at
    if (motorConfig == 0) {
      // Body is not flipped
      releaseGrip(bottomGrip);
      delay(1000);
      flip();
      motorConfig = 180;
      grip(bottomGrip);
      count++;
    } else {
      releaseGrip(topGrip); // In this case, actually the bottom gripper
      delay(1000);
      unflip();
      motorConfig = 0;
      grip(topGrip);
      count++;
    }
  } else {
    // body is at the top so must climb down
    for (int i = 0; i < count; ++i) {
      // ie how many flips it took to get up which is equal to the flips taken to get down
      if (motorConfig == 0) {
        // similar to climbing up except the top gripper is released instead to allow for descending
        releaseGrip(topGrip);
        delay(1000);
        flip();
        motorConfig = 180;
        grip(topGrip);
      } else {
        releaseGrip(bottomGrip);
        delay(1000);
        unflip();
        motorConfig = 0;
        grip(bottomGrip);
      }
    }
    while(1) {
      // infinite loop since task is complete
    }
  }
}

void flip() {
  // Basically flipping the bottom gripper to top if the bottomGripper is disengaged
  // OR
  // Flipping the top gripper to bottom if the topGripper is disengaged
  fourth.write(90);
  delay(1000);
  third.write(90);
  delay(1000);
  second.write(90);
  delay(1000);
  first.write(90); // Rotate clockwise to 90 degrees
  delay(1000);
}

void unflip() {
  // This is the opposite to move the topGripper back from the bottom to the top
  first.write(0);
  delay(1000);
  second.write(0);
  delay(1000);
  third.write(0);
  delay(1000);
  fourth.write(0);
  delay(1000);
}

void releaseGrip(Servo theServo) {
  // Incremental for slower speed and better control
  for (int angle = 0; angle <= 180; angle++) { // Rotate from 0 to 180 degrees opening the gripper
    theServo.write(angle); // Send angle value to servo
    delay(15); // Delay for smoothness
  }
}

void grip(Servo theServo) {
  for (int angle = 180; angle >= 0; angle--) { // Rotate from 180 to 0 degrees
    theServo.write(angle); // Send the angle value to the servo
    delay(15); // Delay for smoother movement
  }
}

void printDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calculating distance
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
