#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

#include "person_detection.h"
#include "wifi_functions.h"
#include "globals.h"
#include "flash_storage.h"
#include "display_functions.h"
#include "tick_function.h"

// Task Handles
TaskHandle_t DetectionHandler;
TaskHandle_t TransmitHandler;

// Task functions
void detectionTask(void * pvParameters) {
    while (true) {
        //detectionTick();
        vTaskDelay(50 / portTICK_PERIOD_MS); // Delay for 50 ms
    }
}

void transmitTask(void * pvParameters){
    while(true){
        transmitTick();
        vTaskDelay(150 / portTICK_PERIOD_MS);
    }
}

//WiFiManager wifiManager;

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

    //Create detection task
    xTaskCreate(
        detectionTask, // Function to implement the task
        "Detection Task", // Task name
        10000, // Stack size
        NULL, // Task parameter
        1, // Priority
        &DetectionHandler // Task handle
    );

    //Create transmit task
    xTaskCreate(
            transmitTask,
            "Transmit Task",
            10000,
            NULL,
            2,
            &TransmitHandler
            );
}

// Setting up the timers for the tick function state machine
unsigned long tick_timer1 = 0;
unsigned long tick_timer2 = millis();
int tick_period = 50; //In milliseconds

void loop() {
   //Nothing goes in loop because it is handled by FreeRTOS with the tasks
}