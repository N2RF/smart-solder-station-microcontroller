//
// Created by leslier on 3/29/2025.
//

#include <Arduino.h>
#include <WiFi.h>
#include "globals.h"


String FIRMWARE_VERSION = "1.0.0";
const String macAddress = WiFi.macAddress();

String stationName = "Smart-Soldering-Station";

boolean personDetected = false;

int stationNumber = 0;
int watts = 83;

const String serverAddress = "https://smart-solder-station.fly.dev";