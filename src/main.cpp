#include "main.h"

void setup() {
    Serial.begin(9600);
    
    pinMode(LED, OUTPUT);
    pinMode(detectorpin, INPUT_PULLUP);
}

void loop(){ 
    prevdetectorstate = digitalRead(detectorpin);
    beginTime = millis();
    
    while ((millis() - beginTime) < 500) {
        detectorstate = digitalRead(detectorpin);
        if ((prevdetectorstate != detectorstate) && (detectorstate == true)) {
            pulse++;
        }
        prevdetectorstate = detectorstate;
    }
    
    Serial.println((pulse*15), DEC);

    if ((pulse*15) >= 50) {
        digitalWrite(LED, HIGH);
    } else {
        digitalWrite(LED, LOW);
    }

    pulse = 0;
}