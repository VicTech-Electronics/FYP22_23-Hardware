// Define the DIR and STEP pin numbers
const int DIR_PIN = 2;
const int STEP_PIN = 3;

void setup() {
  // Set the DIR and STEP pins as outputs
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
}

void loop() {
  // Rotate the stepper motor clockwise
  digitalWrite(DIR_PIN, HIGH); // Set direction to clockwise
  for (int i = 0; i < 200; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(500); // Adjust step duration as needed
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(500); // Adjust step duration as needed
  }

  delay(1000); // Delay between rotations

  // Rotate the stepper motor counterclockwise
  digitalWrite(DIR_PIN, LOW); // Set direction to counterclockwise
  for (int i = 0; i < 200; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(500); // Adjust step duration as needed
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(500); // Adjust step duration as needed
  }

  delay(1000); // Delay between rotations
}
