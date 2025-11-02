#include <Arduino.h>

#define EN_PIN 4
#define STEP_PIN 5
#define DIR_PIN 6
#define POT_PIN A0

const int maxSteps = 1600;
const int stepDelay = 800;
const int positionTolerance = 20;

int potValue = 0;
int targetPosition = 0;
int currentPosition = 0;
int lastPotValue = 0;

void stepMotor(bool dir) {
  digitalWrite(DIR_PIN, dir);
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(stepDelay);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(stepDelay);
}

void setup() {
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(DIR_PIN, LOW);
  digitalWrite(EN_PIN, LOW);

  // Serial.begin(115200);
}

void loop() {
  potValue = analogRead(POT_PIN);
  targetPosition = map(potValue, 0, 1023, 0, maxSteps);

  int diff = targetPosition - currentPosition;

  if (abs(diff) > positionTolerance) {

    if (diff > 0) {
      stepMotor(HIGH);
      currentPosition++;
    } else {
      stepMotor(LOW);
      currentPosition--;
    }
  } 
  else {
    digitalWrite(STEP_PIN, LOW);
    delay(5);
  }

  lastPotValue = potValue;
}
