#ifndef LED_COMMUNICATION_H
#define LED_COMMUNICATION_H

#include <Arduino.h>

class Tx {
public:
    Tx(int pin) : ledPin(pin) {
        pinMode(ledPin, OUTPUT);
    }

    void turnOn() {
        digitalWrite(ledPin, HIGH);
    }

    void turnOff() {
        digitalWrite(ledPin, LOW);
    }

private:
    int ledPin;
};

class Rx {
public:
    Rx(int pin) : analogPin(pin) {
        pinMode(analogPin, INPUT);
    }

    int readValue() {
        return analogRead(analogPin);
    }

    void calibrate() {
        // Prompt user to place Rx in ambient environment with Tx LED off
        Serial.println("Place Rx in ambient environment with Tx LED off.");
        Serial.println("Send 'c' to continue or 'e' to exit.");
        while (!Serial.available());
        char command = Serial.read();
        if (command == 'e') return;

        // Calibration without Tx LED on
        Serial.println("Calibrating without Tx LED on for 5 seconds...");
        unsigned long startTime = millis();
        while (millis() - startTime < 5000) {
            int sensorValue = analogRead(analogPin);
            Serial.print("Sensor value: ");
            Serial.println(sensorValue);
            delay(500);
        }

        // Prompt user to turn on Tx LED
        Serial.println("Turn on Tx LED.");
        Serial.println("Send 'c' to continue or 'e' to exit.");
        while (!Serial.available());
        command = Serial.read();
        if (command == 'e') return;

        // Calibration with Tx LED on
        Serial.println("Calibrating with Tx LED on for 5 seconds...");
        unsigned long startTimeTx = millis();
        while (millis() - startTimeTx < 5000) {
            int sensorValue = analogRead(analogPin);
            Serial.print("Sensor value with Tx LED on: ");
            Serial.println(sensorValue);
            delay(500);
        }

        // Save calibrated values for later use
        calibratedValue = analogRead(analogPin);
        calibratedValueWithTx = analogRead(analogPin);
    }

    int getCalibratedValue() {
        return calibratedValue;
    }

    int getCalibratedValueWithTx() {
        return calibratedValueWithTx;
    }

private:
    int analogPin;
    int calibratedValue = 0;
    int calibratedValueWithTx = 0;
};

#endif
