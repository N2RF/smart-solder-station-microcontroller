#include <Arduino.h>

#define RELAY_PIN 5

void setup() {

    Serial.begin(11500);
    Serial.println("Hello World");
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);

}

void loop() {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("High");
    delay(5000);
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Low");
    delay(5000);
}