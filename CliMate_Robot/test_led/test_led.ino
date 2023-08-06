#include <Adafruit_NeoPixel.h>

int pin = A2;      // Data pin for the NeoPixel array
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


void setup() {
  // put your setup code here, to run once:
  // Then create a new NeoPixel object dynamically with these values:
  pixels = new Adafruit_NeoPixel(numPixels, pin, pixelFormat);

  // Initialize NeoPixel strip object
  pixels->begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  red_LED();
  green_LED();
  yel_LED();
  blue_LED();
  

}


// Make NeoPixel Red
void red_LED()
{
    pixels->clear(); // Set all pixel colors to 'off'
    for (int i = 0; i < numPixels; i++) { // For each pixel...

        // set pixel to blue
        pixels->setPixelColor(i, pixels->Color(255, 0, 0, 0));

        pixels->show(); // Send the updated pixel colors to the hardware.
        
    }
    delay(5000);
    return;
}

// Make NeoPixel Green
void green_LED()
{
    pixels->clear(); // Set all pixel colors to 'off'
    for (int i = 0; i < numPixels; i++) { // For each pixel...

        // set pixel to blue
        pixels->setPixelColor(i, pixels->Color(0, 255, 0, 0));

        pixels->show(); // Send the updated pixel colors to the hardware.
        
    }
    delay(5000);
    return;    
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
    delay(5000);
    return;
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
    
    delay(5000);
    return;
}
