/**
 * Code used for pin assignments
 */

#ifndef CLIMATE_SCANNING_PINASSIGNMENTS_H
#define CLIMATE_SCANNING_PINASSIGNMENTS_H

//Pin Assignments

// Left wheel PWM control
int EB = 3; // Wheel PWM pin (must be a PWM pin)
int I3 = 5; // Wheel direction digital pin 1
int I4 = 4; // Wheel direction digital pin 2

// Right wheel PWM control
int EA = 9; // Wheel PWM pin (must be a PWM pin)
int I1 = 8; // Wheel direction digital pin 1
int I2 = 10; // Wheel direction digital pin 2

// Left wheel encoder digital pins
const byte SIGNAL_AL = 13; // green wire
const byte SIGNAL_BL = 12; // yellow wire

// Right wheel encoder digital pins
const byte SIGNAL_AR = 6;  // green wire
const byte SIGNAL_BR = 7; // yellow wire

// Sharp Sensors
const int FRONT_SHARP_PIN = A2; // Front Sharp Sensor analog pin
//int sharpR_val = 0;           // Right Sharp Sensor analog pin
//int sharpL_val = 0;           // Left Sharp Sensor analog pin

// LED 
int pin = A1; // Data pin for the NeoPixel array

// Buzzer digital pin
const int buzzer = 2;     

#endif //CLIMATE_SCANNING_PINASSIGNMENTS_H
