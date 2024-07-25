// LED Fade Example for Soldered Dasduino Boards with built-in WS2812 LED.
// Original library by AdaFruit Industries, modified by Soldered.

// Include Soldered WS2812 LED library.
#include "WS2812-SOLDERED.h"

// Create WS LED object for the built-in WS2812 LED.
WS2812 pixels(1, LEDWS_BUILTIN);

// How many brightness steps in one fade step. Change if needed.
int fadeAmount = 50;

// Delay between fade steps in milliseconds. Change if needed.
int delayBeetweenSteps = 20;

// Set the LED color and it's brightness. Change if needed.
uint8_t redValue = 0;
uint8_t greenValue = 64;
uint8_t blueValue = 32;

// Variable used to keep track of the current fade.
int brightness = 0;

void setup()
{
    // Initialize NeoPixel strip object (REQUIRED).
    pixels.begin();
}

void loop()
{
    // Map red, green and blue values to match the fade effect.
    uint8_t red = map(brightness, 0, 255, 0, redValue);
    uint8_t green = map(brightness, 0, 255, 0, greenValue);
    uint8_t blue = map(brightness, 0, 255, 0, blueValue);

    // Send these current red, green and blue channel values to WS LED.
    pixels.setPixelColor(0, pixels.Color(red, green, blue)); // Set the color of built-in WS2812 RGB LED

    // Update the LED!
    pixels.show();

    // Change the brightness for next time through the loop.
    brightness = brightness + fadeAmount;

    // Reverse the direction of the fading at the ends of the fade.
    if (brightness <= 0 || brightness >= 255)
    {
        fadeAmount = -fadeAmount;
    }

    // Wait for 30 milliseconds to see the dimming effect.
    delay(delayBeetweenSteps);
}
