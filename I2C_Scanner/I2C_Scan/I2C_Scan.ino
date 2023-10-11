// Include the standard I2C/Wire library
#include "Wire.h"

void setup()
{
    // Init Wire and Serial communications
    Wire.begin();
    Serial.begin(115200);

    // Print a welcome message to Serial
    Serial.println("\nSoldered I2C Scanner!");
    
}

void loop()
{
    // Create some helper variables for making the I2C requests
    byte error, address;
    int nDevices = 0; // Number of devices
 
    // Print a message to the user
    Serial.println("Scanning...");

    // Let's loop through all the available addresses
    for (address = 1; address < 127; address++)
    {
        // This sketch uses the return value of endTransmisstion
        // A value of 0 means a device did acknowledge the message
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            // Found a device! 
            // Notify the user
            Serial.print("I2C device found at address 0x");
            
            // Print the hex address
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");
            nDevices++; // count the device
        }
        else if (error == 4)
        {
            // In case there was an error, also notify the user
            Serial.print("Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }

    // We just finished checking all possible I2C addresses
    if (nDevices == 0)
        // No devices found? Notify the user
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");

    delay(5000); // Wait 5 seconds before the next scan
}
