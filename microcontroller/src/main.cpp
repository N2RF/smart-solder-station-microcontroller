#include <Arduino.h>

#define RELAY_PIN 5
#define PIR_PIN 4

void setup() {

    Serial.begin(11500);
    Serial.println("Hello World");
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
    pinMode(PIR_PIN, INPUT);


}

void loop() {
//    digitalWrite(RELAY_PIN, HIGH);
//    Serial.println("High");
//    delay(5000);
//    digitalWrite(RELAY_PIN, LOW);
//    Serial.println("Low");
//    delay(5000);
    bool pirStatus;
    pirStatus = digitalRead(PIR_PIN);
//    Serial.print("PIR status: ");
//    Serial.println(pirStatus);
//    delay(500);

    if(pirStatus){
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("Station on");
    } else {
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Station off");
    }
}