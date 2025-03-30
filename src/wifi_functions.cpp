//
// Created by leslier on 3/29/2025.
//

#include <Arduino.h>
#include <WiFi.h>
#include "wifi_functions.h"

void setupWifi(const char* ssid, const char* password) {
    Serial.println("Connecting to WiFi...");
    WiFi.setHostname(("Smart-Soldering-Station" + String(WiFi.macAddress())).c_str());
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("Connected to WiFi!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

}

boolean transmitMessage(boolean stationState){
    Serial.println("Transmitting message");
    return false;
}

