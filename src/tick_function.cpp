//
// Created by Robbie on 3/30/25.
//

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include "flash_storage.h"
#include "wifi_functions.h"
#include "globals.h"
#include "tick_function.h"

WiFiManager wifiManager;

enum WIFI_STATE {
    START,
    ONBOARD,
    TRANSMIT
} wifiState;

void transmitTick() {
    switch (wifiState) { //Transitions
        case START:
            if (!isSetupComplete()) {
                wifiState = ONBOARD;
            } else {
                wifiState = TRANSMIT;
            }
            break;
        case ONBOARD:
            if (!isSetupComplete()) {
                wifiState = ONBOARD;
            } else {
                wifiState = TRANSMIT;
            }
            break;
        case TRANSMIT:
            wifiState = TRANSMIT;
            break;
    }

    switch (wifiState) { //Actions
        case START:
            break;
        case ONBOARD:
            if (!isSetupComplete()) {
                flashStorageInit();

                //Connecting to WiFi using the WiFiManager
                wifiManager.setConfigPortalTimeout(180);
                WiFiManagerParameter station_name("station_name", "Station Name", "", 40);
                wifiManager.addParameter(&station_name);
                wifiManager.startConfigPortal("Smart-Soldering-Station", "lafayette");
                // Serial.println("Entered SSID: " + String(WiFi.SSID()));
                // Serial.println("Entered Password: " + String(WiFi.psk()));
                stationName = station_name.getValue();
                Serial.print("Station Name: ");
                Serial.println(stationName);

                //Writing to flash
                setStationName(stationName);
                setWifiCredentials(WiFi.SSID(), WiFi.psk());
                setSetupComplete(true);
            } else {
                Serial.print("Station Name: ");
                Serial.println(getStationName());
                Serial.print("SSID: ");
                Serial.println(getWifiSsid());
                Serial.print("Password: ");
                Serial.println(getWifiPassword());
                setupWifi(getWifiSsid(), getWifiPassword());
            }
            break;
        case TRANSMIT:
            bool didTransmit = transmitMessage(personDetected);
            break;
    }
}