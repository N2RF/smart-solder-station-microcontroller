//
// Created by leslier on 3/29/2025.
//

#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

extern String FIRMWARE_VERSION;
extern const int FIRMWARE_VERSION_MAJOR;
extern const int FIRMWARE_VERSION_MINOR;
extern const int FIRMWARE_VERSION_PATCH;

extern const String macAddress;

extern String stationName;

extern boolean personDetected;

extern int stationNumber;
extern int watts;

extern const String serverAddress;

#endif //GLOBALS_H
