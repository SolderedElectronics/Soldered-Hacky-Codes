// Include ESP32 EEPROM Library
#include "EEPROM.h"

// Set the EEPROM size in bytes.
#define EEPROM_SIZE 512

// Fill EEPROM with this vlaue.
#define EEPROM_FILL_VALUE 0xFF

void setup()
{
  // Init the Serial communication at 115200 bauds (for messages).
  Serial.begin(115200);

  // Send message.
  Serial.print("EEPROM cleaning...");

  // Init EEPROM library.
  EEPROM.begin(EEPROM_SIZE);

  // Fill the memory with defined value.
  for (int i = 0; i < EEPROM_SIZE; i++)
  {
      EEPROM.write(i, EEPROM_FILL_VALUE);
  }

  // Send changes to the EEPROM.
  EEPROM.commit();

  // Send message for the user.
  Serial.println("done!");
}

void loop()
{
   // Nothing
}
