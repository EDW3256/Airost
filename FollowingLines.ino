// Motor control pins
const int IN1 = 18;
const int IN2 = 5;
const int IN3 = 17;
const int IN4 = 16;
const int ENA = 19;
const int ENB = 4;

// IR sensor pins
const int SensorL = 36;  // Left sensor
const int SensorR = 39;  // Right sensor

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  
  // Initialize motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Initialize sensor pins as inputs
  pinMode(SensorL, INPUT);
  pinMode(SensorR, INPUT);

  Serial.println("Setup complete. Ready to follow the line.");
}

void loop() {
  // Read sensor states
  int leftState = digitalRead(SensorL);
  int rightState = digitalRead(SensorR);

  // Control robot movement based on sensor inputs
  if (leftState == LOW && rightState == LOW) {
    // Move forward
    moveForward();
  } else if (leftState == LOW && rightState == HIGH) {
    // Turn right
    turnRight();
  } else if (leftState == HIGH && rightState == LOW) {
    // Turn left
    turnLeft();
  } else {
    // Stop
    stopMotors();
  }

  delay(100); // Small delay to stabilize sensor readings
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(ENA, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(ENB, HIGH);
  Serial.println("Moving forward");
}

// Function to turn the robot right
void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(ENA, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(ENB, HIGH);
  Serial.println("Turning right");
}

// Function to turn the robot left
void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(ENA, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(ENB, HIGH);
  Serial.println("Turning left");
}

// Function to stop the robot
void stopMotors() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Motors stopped");
}
