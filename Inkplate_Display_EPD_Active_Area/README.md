# Inkplate Display Active Area

It shows the ePaper display active area. It also draws small squares in the corners. This can be useful for detecting defects on the ePaper itself, or it can be useful for testing proper driving sequences.

# Usage
- Set the proper Inkplate board in the Arduino Board menu.
- Compile and upload the code.
- Check the result on the ePaper display

# Connections
Connect the USB to the Board to upload the code.

## Tweaks
- In the .ino file, near the top, with the OUTLINE_COLOR change the color of the outline box (0 = Black, 7 = White).
- In the .ino file, near the top, with the OUTLINE_SIZE set the thickness of the outline box (in pixels).
- In the .ino file, in the Serial.begin(115200) change the baud rate (currently set to 115200 bauds).

# Notes
- This code only works for ESP32. To use it with the Arduino, EEPROM.begin() does not have any arguments, and EEPROM.commit() must be removed.
