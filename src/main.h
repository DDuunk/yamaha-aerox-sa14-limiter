#ifndef MAIN_H
#define MAIN_H

#define DEBUG_MODE

#include "Arduino.h" // Include the Arduino Library

/*
 * Pin defines
 */
#define relayPin 2 // Relay is connected to pin 2 on Arduino
#define detectorPin 3 // Sensor is connect to pin 3 on Arduino

/*
 * Variable defines
 */
unsigned long beginTime = millis(); // Number storage of 32 bits
unsigned int pulse = 0; // Integer storage of 32 bits 
bool detectorstate; // Can either be ON or OFF (1 or 0)
bool prevdetectorstate; // Can either be ON or OFF (1 or 0)

/*
 * Call functions 
 */
void setup();
void loop();

#endif //MAIN_H