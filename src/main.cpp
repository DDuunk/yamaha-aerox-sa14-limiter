#include "main.h"

void setup() {
    Serial.begin(9600);
    
    pinMode(relayPin, OUTPUT);
    pinMode(detectorPin, INPUT_PULLUP);
}

void loop(){ 
    prevdetectorstate = digitalRead(detectorPin);
    beginTime = millis();
    
    while ((millis() - beginTime) < 500) {
        detectorstate = digitalRead(detectorPin);
        if ((prevdetectorstate != detectorstate) && (detectorstate == true)) {
            pulse++;
        }
        prevdetectorstate = detectorstate;
    }
    
    Serial.println((pulse*15), DEC);

    if ((pulse*15) >= 40) {
        digitalWrite(relayPin, LOW);
    } else {
        digitalWrite(relayPin, HIGH);
    }

    pulse = 0;
}