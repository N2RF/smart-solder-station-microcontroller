//
// Created by leslier on 3/29/2025.
//

#ifndef PERSON_DETECTION_H
#define PERSON_DETECTION_H

#define RELAY_PIN 5
#define PIR_PIN 4
#define BUZZER_PIN 3

void setupPins();

inline bool isPersonDetected();

void detectionTick();


#endif //PERSON_DETECTION_H
