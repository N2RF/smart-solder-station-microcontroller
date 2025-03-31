//
// Created by Robbie Leslie on 8/17/2024.
//

#include <Arduino.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include "globals.h"
#include "flash_storage.h"

static Preferences flashStorage;

boolean flashStorageInit(){
    flashStorage.end();
    flashStorage.begin("creds", true, "nvs");

    boolean flashInit = flashStorage.isKey("nvsInit");

    if(!flashInit){
        flashStorage.end();
        flashStorage.begin("creds", false, "nvs");
        flashStorage.putBool("hasCreds", false);
        flashStorage.putString("ssid", "");
        flashStorage.putString("password", "");
        flashStorage.putString("stationName", "");
        flashStorage.putInt("stationNumber", -1);
        flashStorage.putInt("stationPower", -1);
        flashStorage.putBool("nvsInit", true);
    }
    flashStorage.end();
    return true;
}

boolean hasWifiCredentials() {
    flashStorage.end();
    flashStorage.begin("creds", true, "nvs");

    if(flashStorage.getBool("nvsInit", false) == false){
        return false;
    }

    boolean hasCredentials =  flashStorage.getBool("hasCreds", false);
    Serial.println("Has credentials: " + String(hasCredentials));
    flashStorage.end();
    return hasCredentials;
}

boolean setHasWifiCredentials(boolean hasCredentials) {
    flashStorage.end();
    flashStorage.begin("creds", false, "nvs");

    if(flashStorage.getBool("nvsInit", false) == false){
        return false;
    }

    flashStorage.putBool("hasCreds", hasCredentials);
    flashStorage.end();
    return true;
}

boolean setWifiCredentials(String newSsid, String newPassword) {
    flashStorage.end();
    flashStorage.begin("creds", false, "nvs");

    if(flashStorage.getBool("nvsInit", false) == false){
        return false;
    }

    flashStorage.putString("ssid", newSsid);
    flashStorage.putString("password", newPassword);
    flashStorage.putBool("hasCreds", true);

    //Debug print statements
    Serial.println("SSID: " + flashStorage.getString("ssid", ""));
    Serial.println("Password: " + flashStorage.getString("password", ""));
    Serial.println("Has credentials: " + String(flashStorage.getBool("hasCreds", false)));

    flashStorage.end();
    return true;
}

const char* getWifiSsid() {
    flashStorage.end();
    flashStorage.begin("creds", true, "nvs");

    // Check if the key exists
    if (!flashStorage.isKey("ssid")) {
        Serial.println("SSID key does not exist");
    }

    static String storedSsid;
    storedSsid = flashStorage.getString("ssid", "");

    flashStorage.end();
    return storedSsid.c_str();
}

const char* getWifiPassword() {
    flashStorage.end();
    flashStorage.begin("creds", true, "nvs");

    static String storedPassword = flashStorage.getString("password", "");
    flashStorage.end();
    return storedPassword.c_str();
}

void clearWifiCredentials() {
    flashStorage.end();
    flashStorage.begin("creds", false, "nvs");
    flashStorage.clear();
    flashStorage.putBool("hasCreds", false);
    flashStorage.end();
}

boolean setStationName(String newStationName) {
    flashStorage.end();
    flashStorage.begin("creds", false, "nvs");
    flashStorage.putString("stationName", newStationName);
    flashStorage.end();
    return true;
}

String getStationName() {
    flashStorage.end();
    flashStorage.begin("creds", true, "nvs");
    String storedStationName = flashStorage.getString("stationName", "");
    flashStorage.end();
    return storedStationName;
}

void clearStationName() {
    flashStorage.end();
    flashStorage.begin("creds", false, "nvs");
    flashStorage.putString("stationName", "");
    flashStorage.end();
}

boolean setStationNumber(int newStationNumber) {
    flashStorage.end();
    flashStorage.begin("creds", false, "nvs");
    flashStorage.putInt("stationNumber", newStationNumber);
    flashStorage.end();
    return true;
}

int getStationNumber() {
    flashStorage.end();
    flashStorage.begin("creds", true, "nvs");
    int storedStationNumber = flashStorage.getInt("stationNumber", -1);
    flashStorage.end();
    return storedStationNumber;
}

void clearStationNumber(){
    flashStorage.end();
    flashStorage.begin("creds", false, "nvs");
    flashStorage.putInt("stationNumber", -1);
    flashStorage.end();
}

boolean setStationPower(int newStationPower) {
    flashStorage.end();
    flashStorage.begin("creds", false, "nvs");
    flashStorage.putInt("stationPower", newStationPower);
    flashStorage.end();
    return true;
}

int getStationPower() {
    flashStorage.end();
    flashStorage.begin("creds", true, "nvs");
    int storedStationPower = flashStorage.getInt("stationPower", -1);
    flashStorage.end();
    return storedStationPower;
}

void clearStationPower(){
    flashStorage.end();
    flashStorage.begin("creds", false, "nvs");
    flashStorage.putInt("stationPower", -1);
    flashStorage.end();
}

boolean setSetupComplete(boolean setupComplete) {
    flashStorage.end();
    flashStorage.begin("creds", false, "nvs");
    flashStorage.putBool("setupComplete", setupComplete);
    flashStorage.end();
    return true;
}

boolean isSetupComplete() {
    flashStorage.end();
    flashStorage.begin("creds", true, "nvs");
    boolean setupComplete = flashStorage.getBool("setupComplete", false);
    flashStorage.end();
    return setupComplete;
}

