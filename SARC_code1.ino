// Include necessary libraries
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

// Define pins for the ultrasonic distance sensor
#define TRIGGER_PIN A1
#define ECHO_PIN A0

// Define the maximum distance for the ultrasonic sensor to measure
#define MAX_DISTANCE 300

// Define the pin for the infrared sensor
#define IR A5

// Create instances of the motor objects for controlling the motors
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Create an instance of the NewPing library for the ultrasonic sensor
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Create an instance of the Servo library for controlling the servo motor
Servo myservo;

// Define a string variable to store voice commands
String voice;

void setup() {
  // Initialize serial communication with the baud rate of 9600
  Serial.begin(9600);

  // Attach the servo motor to pin 10
  myservo.attach(10);

  // Set the initial position of the servo motor to 90 degrees
  myservo.write(90);

  // Set the IR sensor pin as an input
  pinMode(IR, INPUT);
}

void loop() {
  // Measure the distance using the ultrasonic sensor
  int distance = sonar.ping_cm();

  // Check if there is any serial data available to read
  if (Serial.available() > 0) {
    // Clear the previous voice command
    voice = "";
    delay(2);

    // Read the incoming serial data and store it in the voice variable
    voice = Serial.readString();
    delay(2);

    // Print the received voice command to the serial monitor
    Serial.println(voice);

    // Check the received voice command and perform corresponding actions
    if (voice == "turn left" || voice == "left") {
      // Turn the robot left
      left();
    } else if (voice == "turn right" || voice == "right") {
      // Turn the robot right
      right();
    }
  }

  // Continuously move the robot forward while the voice command is "move forward"
  while (voice == "move forward") {
    forward();
  }

  // Continuously move the robot backward while the voice command is "move backward"
  while (voice == "move backward") {
    backward();
  }

  // Stop the robot while the voice command is "stop"
  while (voice == "stop") {
    Stop();
  }
}

// Function to move the robot forward
void forward() {
  // Measure the distance using the ultrasonic sensor
  int distance = sonar.ping_cm();

  // Check if there is an obstacle closer than 10 cm
  if (distance < 10) {
    // Stop the robot if an obstacle is detected
    Stop();
    voice = "";
  } else {
    // Set the motor speeds to move the robot forward
    motor1.setSpeed(255);
    motor1.run(FORWARD);
    motor2.setSpeed(255);
    motor2.run(FORWARD);
    motor3.setSpeed(255);
    motor3.run(FORWARD);
    motor4.setSpeed(255);
    motor4.run(FORWARD);
  }
}

// Function to move the robot backward
void backward() {
  // Read the value from the infrared sensor
  int IR_Sensor = digitalRead(IR);

  // Check if there is an obstacle detected by the infrared sensor
  if (IR_Sensor == 0) {
    // Stop the robot if an obstacle is detected
    Stop();
    voice = "";
  } else {
    // Set the motor speeds to move the robot backward
    motor1.setSpeed(255);
    motor1.run(BACKWARD);
    motor2.setSpeed(255);
    motor2.run(BACKWARD);
    motor3.setSpeed(255);
    motor3.run(BACKWARD);
    motor4.setSpeed(255);
    motor4.run(BACKWARD);
  }
}

// Function to turn the robot left
void left() {
  // Rotate the servo motor to the left position
  myservo.write(180);
  delay(500);
  myservo.write(90);
  delay(500);

  // Set the motor speeds and directions to turn the robot left
  motor1.run(BACKWARD);
  motor1.setSpeed(255);
  motor2.run(BACKWARD);
  motor2.setSpeed(255);
  motor3.run(FORWARD);
  motor3.setSpeed(255);
  motor4.run(FORWARD);
  motor4.setSpeed(255);

  // Delay to turn left for a specific duration
  delay(700);

  // Release all motors to stop moving
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

// Function to turn the robot right
void right() {
  // Rotate the servo motor to the right position
  myservo.write(0);
  delay(500);
  myservo.write(90);
  delay(500);

  // Set the motor speeds and directions to turn the robot right
  motor1.run(FORWARD);
  motor1.setSpeed(255);
  motor2.run(FORWARD);
  motor2.setSpeed(255);
  motor3.run(BACKWARD);
  motor3.setSpeed(255);
  motor4.run(BACKWARD);
  motor4.setSpeed(255);

  // Delay to turn right for a specific duration
  delay(700);

  // Release all motors to stop moving
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

// Function to stop all motors and halt the robot
void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
