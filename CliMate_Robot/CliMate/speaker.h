/**
 * Code used for turning on speaker
 * For collision avoidance/warning
 */
#ifndef CLIMATE_ROBOT_SPEAKER_H
#define CLIMATE_ROBOT_SPEAKER_H

// Required Libraries
#include "pinAssignments.h"
#include "lights.h"

// Variable Initilization 
float distanceFromObj;
float sharpF_val;

// Function Decleration
void speaker_setup();
int collision_warning();
float convertDistance (float sharpVal);
void warning();

void speaker_setup()
{
  pinMode(buzzer, OUTPUT); // Set buzzer pin as an output
}


// Function to warn of collision
int collision_warning()
{
    int flag = 0;
    // Read the sensor output (0-1023, which is 10 bits and fits inside an Arduino int-type)
    sharpF_val = analogRead(FRONT_SHARP_PIN);
//    sharpL_val = analogRead(LEFT_SHARP_PIN);
//    sharpR_val = analogRead(RIGHT_SHARP_PIN);

    // If object is too close sound alarm
    float reading = convertDistance(sharpF_val);
//    Serial.print(reading);
//    Serial.print('\n');
    if (reading < 15.0)
    {
      red_LED();
      // warning();
      flag = 1;
    }
//    Serial.print(flag);
//    Serial.print('\n');
    // Delay for a bit before reading the sensor again
    //delay(500);
    
    return flag;
}

float convertDistance (float sharpVal)
{
  // 112.12*e^(-0.005*sharpVal)
  distanceFromObj = (112.12 * exp((-0.005*sharpVal)));
  return distanceFromObj;
}

// Function to run buzzer
void warning()
{
     // Write noise to speaker
     // Send 1KHz sound signal...    
}
#endif //CLIMATE_ROBOT_SPEAKER_H
