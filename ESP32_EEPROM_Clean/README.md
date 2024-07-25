# ESP32 EEPROM Clean
Simple sketch that clear EEPROM content onthe ESP32 MCU using Arduino IDE.

# Usage
Upload the code to the Dasduino Board, open Arduino Serial Monitor and wait for EEPROM clean process to finish.

# Connections
There are no any (except USB communication - Arduino Serial Monitor).

# Tweaks
- `#define EEPROM_SIZE 512` Defined size of the EEPROM - Clean chunk size.
- `#define EEPROM_FILL_VALUE 0xFF` What value EEPROM will be filled with.
- `Serial.print("EEPROM cleaning...");` Message to notify user the EEPROM Clean process started.
- `Serial.println("done!");` Message to notify user the EEPROM Clean process ended.

# Notes
This sketch only works on ESP32 with Arduino IDE.
