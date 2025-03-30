//
// Created by leslier on 3/29/2025.
//

#include <Arduino.h>
#include "person_detection.h"



void setupPins() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
    pinMode(PIR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

inline bool isPersonDetected() {
    return digitalRead(PIR_PIN);
}


static bool previousMotion = false;
static int debounceCounter = 0;
static constexpr int debounceThreshold = 300; //Change this to change debounce time
static constexpr int debounceMotion = 180; //Change this to change debounce time
static constexpr int debounceOff = 250; //Change this to change debounce time


enum MOTION_STATE {
    START,
    MOTION_DETECTED,
    DEBOUNCE,
    OFF
} motionState;

static const char* motionStateToString(const MOTION_STATE state) {
  switch (state) {
  case START: return "START";
  case MOTION_DETECTED: return "MOTION_DETECTED";
  case DEBOUNCE: return "DEBOUNCE";
  case OFF: return "OFF";
  default: return "UNKNOWN";
  }
}

void detectionTick(){

  Serial.print("PIR status: ");
  Serial.println(isPersonDetected());
  Serial.print("Motion state: ");
  Serial.println(motionStateToString(motionState));
  Serial.print("Debounce counter: ");
  Serial.println(debounceCounter);

  switch(motionState){ //Transistions
    case START:
      motionState = OFF;
    debounceCounter = 0;
    previousMotion = false;
      break;
    case MOTION_DETECTED:
      if (isPersonDetected()) {
        motionState = MOTION_DETECTED;
      } else {
        motionState = DEBOUNCE;
      }
      break;
    case DEBOUNCE:
      if ( debounceCounter >= debounceThreshold) { //upper edge
        motionState = MOTION_DETECTED;
      } else if (debounceCounter == 0) { //lower edge
        motionState = OFF;
        debounceCounter = 0;
      } else if (isPersonDetected() && debounceCounter < debounceThreshold) {
        debounceCounter++;
        motionState = DEBOUNCE;
      } else if (!isPersonDetected() && debounceCounter < debounceThreshold) {
        motionState = DEBOUNCE;
        debounceCounter--;
      }
      break;
    case OFF:
      if (isPersonDetected()) {
        motionState = DEBOUNCE;
      } else {
        motionState = OFF;
      }
      break;

    }

  switch(motionState){ //Actions
  case START:
    debounceCounter = debounceMotion;
    digitalWrite(RELAY_PIN, LOW);
    break;
  case MOTION_DETECTED:
    debounceCounter = debounceMotion;
    digitalWrite(RELAY_PIN, HIGH);
    break;
  case DEBOUNCE:
    break;
  case OFF:
    debounceCounter = debounceOff;
    digitalWrite(RELAY_PIN, LOW);
    break;
  }
}