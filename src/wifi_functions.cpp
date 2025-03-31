//
// Created by leslier on 3/29/2025.
//

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "globals.h"
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

//HTTPS client
WiFiClientSecure wifiClient;
HTTPClient httpClient;

void setupHTTP(){
    wifiClient.setInsecure(); //TODO test if we can do it securely
    if(!wifiClient.connect(serverAddress.c_str(), 3001)){ //TODO might need to change this
        Serial.println("Connection failed");
    }
}


boolean onboardIron(){
    JsonDocument device_data;
    JsonDocument received_data;

    const String endpoint = "/device/manage";
    String route = serverAddress + endpoint;

    Serial.println("Starting HTTPS request");
    if(!httpClient.begin(wifiClient, route)){
        Serial.println("Failed to start HTTPS connection");
        return false;
    }

    device_data["mac_address"] = macAddress;
    device_data["bench_id"] = stationNumber;
    device_data["wats_per_hour"] = watts;
    String device_data_string;
    serializeJson(device_data, device_data_string);
    Serial.println("Sending POST request...");

    httpClient.addHeader("Content-Type", "application/json");
    int httpCode = httpClient.POST(device_data_string);

    //TODO finish checking this
    if(httpCode > 0){
        String responseBody = httpClient.getString();
        Serial.println("Response body: " + responseBody);
        httpClient.end();
        if(httpCode == 200){
            Serial.println("Onboarded successfully");
            return true;
        } else if (httpCode == 401){
            Serial.println("Unauthorized");
            return false;
        } else if(httpCode == 400){
            Serial.println("Bad request");
            return false;
        } else if(httpCode == 500){
            Serial.println("Internal server error");
            return false;
        } else {
            Serial.println("Failed to update machine status: Unknown error");
            return false;
        }
    }
    Serial.println("Microcontroller error on transmitting");
    return false;
}

boolean transmitMessage(boolean stationState){
    Serial.println("Transmitting message");
    return false;
}

