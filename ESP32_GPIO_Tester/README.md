# ESP32 GPIO Tester
Test code for testing GPIO pins. The code will set the selected ESP32 GPIO to HIGH and all other pins to LOW (it will read the pin state if the pin is INPUT ONLY).

# Usage
Upload the code on the ESP32 dev board that needs to be tested, open the serial monitor @ 115200 bauds, set CR and LF, and send the GPIO pin number that needs to be tested.

# Connections
There are no any (except USB communication)

# Tweaks
Can modify allowed pin in the LUT called "gpios" and "gpiosInputOnly" and can change the baud rate in Serial.begin().

# Notes
For input-only pins, the state on the pin can't be set, but in that case, code will read the state of the pin and send it to the Serial. It will enable pull-up resistor on this pin!
