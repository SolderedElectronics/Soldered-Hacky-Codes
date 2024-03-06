# Inkplate VCOM Factory Programmings
This code enables to program custom VCOM voltage into Inkplate ePaper PMIC (TPS65186) without using Inkplate Factory VCOM programming with all hardware tests.

# Usage
- Set the proper VCOM voltage in the code (double vcomVoltage = -2.35).
- Compile and upload the code.
- Open Arduino Serial Monitor and send "secret key" to confirm VCOM programming.

# Connections
Connect the USB to the Board to upload the code and ePaper to the appropriate connector.

## Tweaks
- In the .ino file, near the top, change the VCOM volgate (by default is set to -2.35V). Range is from 0V to -5V.
- In the .ino file, near the top, change the "secret key" (default is "CONTINUE").

# Notes
- !!!WARNING!!! You can only reprogram the VCOM voltage in the TPS65186 about 100 times after which the last programmed VCOM becomes permanent VCOM voltage!
