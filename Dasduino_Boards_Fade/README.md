# Dasduino Boards Fade
Simple sketch that fades built-in WS2812 LED found on every Dasduino board. It allows color change as well as how fast fade and fade change is.

# Usage
Upload the code to the Dasduino Board with build-in WS2812 LED or any other board with added WS2812 LED.

# Connections
There are no any (except USB communication) if used Dasduino boards with built-in WS2812 LED. Otherwise WS2812 LED must be connected to the corresponding GPIO pin as well as power pins for LED.

# Tweaks
- `WS2812 pixels(1, LEDWS_BUILTIN);` Changing first parameter in constructor allows to change the numner of LEDs in string, second allows to set user-defined GPIO pin for LED.
- `int fadeAmount = 50;` Change how fast brightness value changes for 1 to 255.
- `int delayBeetweenSteps = 20;` Change how fast fade is happening.
- `uint8_t redValue = 0;` Change the red channel value (brightness) of the fade color.
- `uint8_t greenValue = 64;` Change the green channel value (brightness) of the fade color.
- `uint8_t blueValue = 32;` Change the blue channel value (brightness) of the fade color.

# Notes
None.
