/* BLUETOOTH CAR WITH ARDUINO UNO AND HC-05
   This code demonstrates controlling a car via smartphone using Bluetooth communication
   with a single servo for the gripper mechanism.
*/

#include <Servo.h> // Include the Servo library

#define in1 A3
#define in2 A2
#define in3 A1
#define in4 A0

Servo servo1; // Create servo object for the servo

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(9,  OUTPUT); 
  pinMode(10, OUTPUT);
  
  // Attach the servo
  servo1.attach(5); // Servo signal pin connected to digital pin 5

  // Initialize servo at neutral position
  servo1.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    char inputvalue = char(Serial.read());

    // Controlling speed (0 = off and 255 = max speed)
    analogWrite(9, 200); // ENA pin
    analogWrite(10, 200); // ENB pin

    // Move forward
    if (inputvalue == 'F') {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    // Move backward
    else if (inputvalue == 'B') {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }
    // Turn right
    else if (inputvalue == 'R') {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    // Turn left
    else if (inputvalue == 'L') {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
    // Stop the car
    else if (inputvalue == 'S') {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
    // Gripper commands for one servo
    if (inputvalue == 'G') { // Open gripper
      servo1.write(180); // Servo rotates forward
      delay(1000);       // Adjust the delay for desired opening extent
      servo1.write(90);  // Stop servo
    } else if (inputvalue == 'H') { // Close gripper
      servo1.write(90);   // Servo rotates backward
      delay(1000);       // Adjust the delay for desired closing extent
      servo1.write(90);  // Stop servo
    }
  }
}
