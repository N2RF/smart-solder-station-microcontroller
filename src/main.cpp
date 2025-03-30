#include <Arduino.h>
#include <WiFi.h>

#include "person_detection.h"
#include "wifi_functions.h"
#include "globals.h"
#include "flash_storage.h"
#include "wifi_secrets.h"
#include "display_functions.h"

// Task Handles
TaskHandle_t DetectionHandler;

// Task functions
void detectionTask(void * pvParameters) {
    while (true) {
        detectionTick();
        vTaskDelay(50 / portTICK_PERIOD_MS); // Delay for 50 ms
    }
}


void setup() {

    Serial.begin(11500);
    delay(2000);
    Serial.println("Hello World");
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
    pinMode(PIR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);

    setupScreen();

    if (!isSetupComplete()) {
        flashStorageInit();
    } else {
        Serial.print("Station Name: ");
        Serial.println(getStationName());
    }

    setupWifi(WIFI_SSID, WIFI_PASSWORD);

    //Create detection task
    xTaskCreate(
        detectionTask, // Function to implement the task
        "Detection Task", // Task name
        10000, // Stack size
        NULL, // Task parameter
        1, // Priority
        &DetectionHandler // Task handle
    );
}

// Setting up the timers for the tick function state machine
unsigned long tick_timer1 = 0;
unsigned long tick_timer2 = millis();
int tick_period = 50; //In milliseconds

void loop() {
    // digitalWrite(RELAY_PIN, HIGH);
    // Serial.println("High");
    // delay(1000);
    // digitalWrite(RELAY_PIN, LOW);
    // Serial.println("Low");
    // delay(1000);
//    // const bool pirStatus = digitalRead(PIR_PIN);
//    Serial.print("PIR status: ");
//    Serial.println(pirStatus);
//    delay(500);

    // if(pirStatus){
    //     digitalWrite(RELAY_PIN, HIGH);
    //     //digitalWrite(BUZZER_PIN, HIGH);
    //     Serial.println("Station on");
    // } else {
    //     digitalWrite(RELAY_PIN, LOW);
    //     //digitalWrite(BUZZER_PIN, LOW);
    //     Serial.println("Station off");
    // }

    // //Updating the tick functions timers
    // tick_timer2 = millis();
    //
    // if ((tick_timer2 - tick_timer1) >= tick_period) {
    //     //Serial.println("Tick function reached");
    //     detectionTick();
    //     tick_timer1 = tick_timer2;
    // }
}