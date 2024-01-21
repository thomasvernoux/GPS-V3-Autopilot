#include <AccelStepper.h>

#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1

#define buttonCW 4  // Connect clockwise button to digital pin 4
#define buttonCCW 5 // Connect counterclockwise button to digital pin 5
#define potPin A0    // Connect potentiometer to analog pin A0

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
int speed = 0; // Initial speed

void setup() {
  pinMode(buttonCW, INPUT_PULLUP);
  pinMode(buttonCCW, INPUT_PULLUP);

  stepper.setMaxSpeed(10000);
  stepper.setAcceleration(10);
}

void loop() {
  // Read the value from the potentiometer
  int potValue = analogRead(potPin);
  
  // Map the potentiometer value to the speed range (adjust the values as needed)
  speed = map(potValue, 0, 1023, 1000, 20000);

  // Check the state of the clockwise button
  if (digitalRead(buttonCW) == LOW) {
    stepper.setSpeed(speed);
    stepper.move(1000); // Adjust the steps as needed
    stepper.runSpeedToPosition();
  }

  // Check the state of the counterclockwise button
  if (digitalRead(buttonCCW) == LOW) {
    stepper.setSpeed(-speed); // Negative speed for counterclockwise
    stepper.move(-1000); // Adjust the steps as needed
    stepper.runSpeedToPosition();
  }
}
