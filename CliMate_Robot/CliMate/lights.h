/**
 * Code used for turning LEDs ON
 * Will be accessed through logic in the robots operation
 * Colours signifie state/operation
 * RED -> Failure to read from sensor
 * GREEN -> Operating as it should, i.e. scanning
 * YELLOW -> Sensors are initializing
 * BLUE -> Sensing object and/or pausing scanning
 * !!!Split parts into functions where applicable!!!
 */

#ifndef CLIMATE_SCANNING_LIGHTS_H
#define CLIMATE_SCANNING_LIGHTS_H
#include <Adafruit_NeoPixel.h>


int numPixels = 8; // Define the number of NeoPixels on the board

// NeoPixel color format & data rate.
// We have an RGBW pixel array (there is colour and a white pixel).
int pixelFormat = NEO_RGBW + NEO_KHZ800;

// Create a pointer for the NeoPixel object (must be outside all functions)
Adafruit_NeoPixel *pixels;

// Function Decleration
void lights_setup();
void red_LED();
void green_LED();
void green_LED_Flash();
void yel_LED();
void blue_LED();

void lights_setup()
{
    // Then create a new NeoPixel object dynamically with these values:
    pixels = new Adafruit_NeoPixel(numPixels, pin, pixelFormat);

    // Initialize NeoPixel strip object
    pixels->begin();
}

// Make NeoPixel Red
void red_LED()
{
    pixels->clear(); // Set all pixel colors to 'off'
    for (int i = 0; i < numPixels; i++) { // For each pixel...

        // set pixel to blue
        pixels->setPixelColor(i, pixels->Color(0, 255, 0, 0));

        pixels->show(); // Send the updated pixel colors to the hardware.
    }
}

// Make NeoPixel Green
void green_LED()
{
    pixels->clear(); // Set all pixel colors to 'off'
    for (int i = 0; i < numPixels; i++) { // For each pixel...

        // set pixel to blue
        pixels->setPixelColor(i, pixels->Color(255, 0, 0, 0));

        pixels->show(); // Send the updated pixel colors to the hardware.

    }
}

// Make NeoPixel Yellow
void yel_LED()
{
    pixels->clear(); // Set all pixel colors to 'off'
    for (int i = 0; i < numPixels; i++) { // For each pixel...

        // set pixel to blue
        pixels->setPixelColor(i, pixels->Color(255, 255, 0, 0));

        pixels->show(); // Send the updated pixel colors to the hardware.

    }
}

// Make NeoPixel Blue
void blue_LED()
{
    pixels->clear(); // Set all pixel colors to 'off'
    for (int i = 0; i < numPixels; i++) { // For each pixel...

        // set pixel to blue
        pixels->setPixelColor(i, pixels->Color(0, 0, 255, 0));

        pixels->show(); // Send the updated pixel colors to the hardware.

    }
}

#endif //CLIMATE_SCANNING_LIGHTS_H
