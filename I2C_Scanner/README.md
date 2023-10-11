# I2C Scanner for Arduino-Compatible devices

A simple sketch which checks results of transmitting to all available I2C addreses and lets you know which ones have a follower device connected. Really useful for when you want to check if a sensor is even reachable over I2C when troubleshooting. It's compatible essentially with all Arduino-compatible microcontrollers.

# Usage
- Connect all peripheral I2C devices you want to test to your main microcontroller
- Upload this code using the Arduino IDE with the correct board definition
- Open the Serial monitor at 115200 baud!

# Connections
Standard I2C connections or use an easyC cable.

## Tweaks
- Change the 'Wire' object to whatever I2C interface you're using
