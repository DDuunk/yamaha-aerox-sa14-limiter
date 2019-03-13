#include "main.h" // Include our library

void setup() {
    // Opens a Serial Port on 9600 baudrate for debugging purposes
    Serial.begin(9600);

    // PinMode defines
    pinMode(relayPin, OUTPUT);        // Relay is an output
    pinMode(sensorPin, INPUT);        // Sensor is an input

    beginTime = millis(); // Start the clock
}

void loop() {
    sensorValue = analogRead(sensorPin); // Read the value of the hall sensor

    if (sensorValue > threshold) {
        // reset beginTime
        beginTime = millis(); // Set beginTime to current beginTime
        // Turn limiter off
        digitalWrite(relayPin, LOW);
    } 
    
    if (sensorValue < threshold && (millis() - beginTime) > 1000) {
        // Turn limiter on
        digitalWrite(relayPin, HIGH);
    }
}
