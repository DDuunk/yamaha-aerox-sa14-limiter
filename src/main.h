#ifndef MAIN_H
#define MAIN_H

#define DEBUG_MODE

#include "Arduino.h"

#define LED 2
#define detectorpin 3

unsigned long beginTime = millis();
unsigned int pulse = 0;
bool detectorstate;
bool prevdetectorstate;

void setup();
void loop();

#endif //MAIN_H