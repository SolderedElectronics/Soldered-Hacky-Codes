// Include Inkplate library to the sketch
#include "Inkplate.h"

// Include Arduino Wire libary.
#include "Wire.h"

// Create Inkplate object.
Inkplate display(INKPLATE_1BIT);

// Wanted VCOM voltage. For Inkplate5 panel use -2.35V.
double vcomVoltage = -2.35;

// "Secret key" for proceed VCOM programming.
const char* secretKey = "CONTINUE";

void setup()
{
    // Initialize serial communication at 115200 bauds.
    Serial.begin(115200);

    // Send message.
    Serial.println("Code started!");

    // Initialize Inkplate library.
    display.begin();

    // Set INT pin from the TPS65186 PMIC to input, pullup.
    display.pinModeInternal(IO_INT_ADDR, display.ioRegsInt, 6, INPUT_PULLUP);

    // Send message to notify the user to proceed with the VCOM programming.
    Serial.printf("Send [%s] to proceed with VCOM programming (it's case sensitive!): \r\n", secretKey);

    // Wait until you got the data from the Serial.
    while (Serial.available() <= 0);

    if (!gotTheKey())
    {
        // Send the message.
        Serial.println("Wrong command, reset the board if needed!");
    }
    else
    {
        writeVCOMToEEPROM(vcomVoltage);
    }
}

void loop()
{
    // Empty...
}

uint8_t writeVCOMToEEPROM(double v)
{
    int vcom = int(abs(v) * 100);
    int vcomH = (vcom >> 8) & 1;
    int vcomL = vcom & 0xFF;

    // Set PCAL pin where TPS65186 INT pin is connectet to input pull up
    display.pinModeInternal(IO_INT_ADDR, display.ioRegsInt, 6, INPUT_PULLUP);

    // First power up TPS65186 so we can communicate with it
    display.einkOn();

    // Wait a little bit
    delay(250);

    // Send to TPS65186 first 8 bits of VCOM
    writeReg(0x03, vcomL);

    // Send new value of register to TPS
    writeReg(0x04, vcomH);
    delay(1);

    // Program VCOM value to EEPROM
    writeReg(0x04, vcomH | (1 << 6));

    // Wait until EEPROM has been programmed
    delay(100);
    do
    {
        delay(1);
    } while (display.digitalReadInternal(IO_INT_ADDR, display.ioRegsInt, 6));

    // Clear Interrupt flag by reading INT1 register
    readReg(0x07);

    // Now, power off whole TPS
    display.einkOff();

    // Wait a little bit...
    delay(1000);

    // Power up TPS again
    display.einkOn();

    delay(10);

    // Read VCOM valuse from registers
    vcomL = readReg(0x03);
    vcomH = readReg(0x04);

    // Trun off the TPS65186 and wait a little bit
    display.einkOff();
    delay(100);

    if (vcom != (vcomL | (vcomH << 8)))
    {
        Serial.println("\nVCOM EEPROM PROGRAMMING FAILED!\n");
        return 0;
    }
    else
    {
        Serial.println("\nVCOM EEPROM PROGRAMMING OK\n");
        return 1;
    }
    return 0;
}

bool gotTheKey()
{
    // Capture the timestamp.
    unsigned long _myTimer = millis();

    // Capture the last number of received chars in the buffer.
    int _lastAvailableSerial = Serial.available();

    // Wait until the last char has been received.
    while ((unsigned long)(millis() - _myTimer) < 50ULL)
    {
        // If you still got the new chars, update the timeout value.
        if (Serial.available() != _lastAvailableSerial)
        {
            // Update the timer.
            _myTimer = millis();

            // Update the variable.
            _lastAvailableSerial = Serial.available();
        }
    }

    // Now try to find the key.
    return Serial.find(secretKey);
}

// Functions that writes data in register over I2C communication
void writeReg(uint8_t _reg, uint8_t _data)
{
    Wire.beginTransmission(0x48);
    Wire.write(_reg);
    Wire.write(_data);
    Wire.endTransmission();
}

// Functions that reads data from register over I2C communication
uint8_t readReg(uint8_t _reg)
{
    Wire.beginTransmission(0x48);
    Wire.write(_reg);
    Wire.endTransmission(false);
    Wire.requestFrom(0x48, 1);
    return Wire.read();
}
