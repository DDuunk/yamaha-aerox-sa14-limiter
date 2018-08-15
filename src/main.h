#ifndef MAIN_H
#define MAIN_H

#define DEBUG_MODE

#include "Arduino.h"

#define LED 2
#define detectorpin 3

unsigned long begintijd = millis();
unsigned int pulsen = 0;

void setup();
void loop();

#endif //MAIN_H