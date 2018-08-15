#include "main.h"

void setup() {
    Serial.begin(9600);
    
    pinMode(LED, OUTPUT);
    pinMode(detectorpin, INPUT_PULLUP);
}

void loop(){ 
    bool prevdetectorstate = digitalRead(detectorpin);
    bool detectorstate;
    begintijd = millis();
    
    while ((millis() - begintijd) < 500) {
    detectorstate = digitalRead(detectorpin);
    if ((prevdetectorstate != detectorstate) && (detectorstate == true)) {
        pulsen++;
    }
    prevdetectorstate = detectorstate;
    }
    
    Serial.println((pulsen*15), DEC);
    pulsen = 0;
}