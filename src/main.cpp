#include "main.h" // Include our library

void setup() {
    // Opens a Serial Port on 9600 baudrate for debugging purposes
    Serial.begin(9600);

    
    // PinMode defines
    pinMode(relayPin, OUTPUT);        // Relay is an output
    pinMode(sensorPin, INPUT_PULLUP); // Sensor is an input with a pullup resistor
}

void loop() {
    // Sign prevdetectorstate to the value of sensorPin
    prevdetectorstate = digitalRead(sensorPin);
    beginTime = millis();             // Start millis

    // When the current millis - beginTime is less then 500ms
    // - First sign detectorstate to the value of sensorPin
    // - If prevdetectorstate is not equal to detectorstate AND detectorstate 
    //   has the value of true: add a pulse
    // - Sign prevdetectorstate to detectorstate to reset
    while ((millis() - beginTime) < 500) {
        detectorstate = digitalRead(sensorPin);
        if ((prevdetectorstate != detectorstate) && (detectorstate == true)) {
            pulse++;
        }
        prevdetectorstate = detectorstate;
    }

    // Print the value of pulse * 15 to the Serial port and convert the value to decimal
    #ifdef DEBUG_MODE
        Serial.println((pulse * 15), DEC); 
    #endif
    
    // If the value of pulse * 15 is bigger or equal to 40: turn relay ON
    // If the value of pulse * 15 is lower than 40 : turn relay off
    // Because of the pullup resistor LOW == ON and HIGH == OFF!
    if ((pulse * 15) >= 40) {
        digitalWrite(relayPin, LOW);
    } else {
        digitalWrite(relayPin, HIGH);
    }

    pulse = 0; // Reset the value of pulse
}