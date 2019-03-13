#ifndef MAIN_H
#define MAIN_H

#define DEBUG_MODE

#include "Arduino.h"                // Include the Arduino Library

// Pin defines
#define relayPin 2                  // Relay is connected to pin 2 on Arduino
#define sensorPin A0                 // Sensor is connect to pin A0 on Arduino

// Variable defines
unsigned long beginTime = millis(); // Number storage of 32 bits
int threshold = ...;                // This number determines at which value the limiter will kick in   
bool detectorstate;                 // Can either be TRUE or FALSE
bool prevdetectorstate;             // Can either be TRUE or FALSE

// Call functions 
void setup();
void loop();

#endif //MAIN_H