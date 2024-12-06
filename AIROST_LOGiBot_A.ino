#include <Servo.h>

// Motor control pins
const int motorA1 = 3;
const int motorA2 = 5;
const int motorB1 = 6;
const int motorB2 = 8;
const int ENA = 9;  // PWM pin for motor A
const int ENB = 10; // PWM pin for motor B

// Servo control pin
const int servoPin = 11;

Servo myServo; // Create servo object

void setup() {
  Serial.begin(9600); // Initialize serial communication

  // Initialize motor control pins as outputs
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize servo motor
  myServo.attach(servoPin);
  myServo.write(90); // Set servo to mid position

  Serial.println("Setup complete. Ready for commands.");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  switch (command) {
    case 'F':
      moveForward(255); // Full speed
      break;
    case 'B':
      moveBackward(255); // Full speed
      break;
    case 'L':
      turnLeft(255); // Full speed
      break;
    case 'R':
      turnRight(255); // Full speed
      break;
    case 'S':
      stopMotors();
      break;
    case 'G': // Open gripper
      openGripper();
      break;
    case 'H': // Close gripper
      closeGripper();
      break;
    default:
      Serial.println("Invalid command");
  }
}

void moveForward(int speed) {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  analogWrite(ENA, speed); // Set speed with PWM
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(ENB, speed); // Set speed with PWM
  Serial.println("Moving forward");
}

void moveBackward(int speed) {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  analogWrite(ENA, speed); // Set speed with PWM
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(ENB, speed); // Set speed with PWM
  Serial.println("Moving backward");
}

void turnLeft(int speed) {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  analogWrite(ENA, speed); // Set speed with PWM
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(ENB, speed); // Set speed with PWM
  Serial.println("Turning left");
}

void turnRight(int speed) {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  analogWrite(ENA, speed); // Set speed with PWM
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(ENB, speed); // Set speed with PWM
  Serial.println("Turning right");
}

void stopMotors() {
  analogWrite(ENA, 0); // Stop motor
  analogWrite(ENB, 0); // Stop motor
  Serial.println("Motors stopped");
}

// Gripper control functions
void openGripper() {
  Serial.println("Opening Gripper");
  myServo.write(180); // Rotate forward

}

void closeGripper() {
  Serial.println("Closing Gripper");
  myServo.write(90);  // Rotate backward
}
