#ifndef CLIMATE_ROBOT_SCANNING_H
#define CLIMATE_ROBOT_SCANNING_H
/**
* Code used for gathering measurements
* Values will be written to python
* SCD30 used for gathering CO2 measurements [ppm],
*  temperature [degC], humidity [relative]
* SGP30 used for gathering TVOC [ppb]
* NeoPixel Stick will emit light according to action being taken
* Currently no hardcoded values will be used for baseline values
*  ideally would use nighttime measurements
*/

// Required Libraries
#include <Adafruit_SCD30.h>
Adafruit_SCD30 scd;
#include <Adafruit_SGP30.h>
Adafruit_SGP30 sgp;
#include "pinAssignments.h"
#include "lights.h"
#include "speaker.h"


// SCD30
const int measurementInterval_SCD = 2;          // Measurement Frequency of SCD30 [2-1800 s]
//
// SGP30
int counter = 0;
unsigned long period = 2000;                    // Measurement period of SGP30 [ms]
unsigned long measurement_time = millis();


// Function Decleration
void scanning_setup();
void SCD30_scanning();
void SGP30_scanning();

void scanning_setup() {

  Serial.begin(9600);

    // Yellow light during initialization
    yel_LED();
  
    // Initialize SCD30 sensor
    if (!scd.begin())
    {
      //red_LED();
      while (1)
      {
          delay(10); // This will stay here forever if a sensor isn't found
      }
    }
    
    // Set measurement interval
    scd.setMeasurementInterval(measurementInterval_SCD);

    // Initialize SGP30 sensor
    if (!sgp.begin())
    {
      //red_LED();
      while (1)
      {
          delay(10); // This will stay here forever if a sensor isn't found
      }
    } 

}


void SCD30_scanning(){
    collision_warning();
  
    // Green light during operation
    green_LED();

    // The SCD30 will report when ready to measure
    if (scd.dataReady())
    {
      // If data cannot be read
      if (!scd.read())
      {
        //red_LED();
        return;
      }

      // Send measured values to Raspberry Pi
      Serial.print(scd.temperature);
      Serial.print(",");
      Serial.print(scd.relative_humidity);
      Serial.print(",");
      Serial.print(scd.CO2);
      Serial.print(",");
      
    }
}


void SGP30_scanning(){
  collision_warning();
  
    // Get the elapsed time [ms]
    int t_now = millis();

    // Green light during operation
    green_LED();
    if (millis() - measurement_time > period)
    {
        measurement_time = millis();

        if (!sgp.IAQmeasure())
        {
          red_LED();
          //Serial.println("Measurement failed");
          return;
        }
        Serial.print(sgp.TVOC);
//        Serial.print(","); //Used for raw measurements
        
        // Raw meausrements
//         if (!sgp.IAQmeasureRaw())
//         {
//           red_LED();
//           return;
//         }
//         Serial.print(sgp.rawH2);
//         Serial.print(",");
//         Serial.print(sgp.rawEthanol);
//         Serial.print(",");

    }

}


#endif //CLIMATE_ROBOT_SCANNING_H
