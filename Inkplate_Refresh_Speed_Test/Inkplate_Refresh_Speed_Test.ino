// Include Inkplate library to our sketch.
#include "Inkplate.h"

// Include images (converted with Inkplate Image Converter)
#include "image1bit.h"
#include "image1bitPartial.h"
#include "image3bit.h"

// Create Inkplate object.
Inkplate display(INKPLATE_1BIT);

void setup()
{
    // Init serial communication and send hello message.
    Serial.begin(115200);
    Serial.println("Test has started");

    // Init Inkplate library
    display.begin();

    // Calculate refresh time of the 1 bit mode, full refresh, switch epaper PMIC.
    Serial.print("1 Bit mode, full refresh, epaper PMIC Switched: ");
    Serial.print(fullRefresh1Bit(0) / 1000.0, 3);
    Serial.println("ms");

    // Wait a little bit
    delay(1000);

    // Calculate refresh time of the 1 bit mode, full refresh, epaper PMIC always on.
    Serial.print("1 Bit mode, full refresh, epaper PMIC always on: ");
    Serial.print(fullRefresh1Bit(1) / 1000.0, 3);
    Serial.println("ms");
    
    // Wait a little bit
    delay(1000);

    // Calculate refresh time of the 1 bit mode, partial refresh, switch epaper PMIC.
    Serial.print("1 Bit mode, partial refresh, epaper PMIC Switched: ");
    Serial.print(partialRefresh1Bit(0) / 1000.0, 3);
    Serial.println("ms");

    // Wait a little bit
    delay(1000);

    // Calculate refresh time of the 1 bit mode, partial refresh, epaper PMIC always on.
    Serial.print("1 Bit mode, partial refresh, epaper PMIC always on: ");
    Serial.print(partialRefresh1Bit(1) / 1000.0, 3);
    Serial.println("ms");
    
    // Wait a little bit
    delay(1000);

    // Calculate refresh time of the 3 bit mode, full refresh, switch epaper PMIC.
    Serial.print("3 Bit mode, full refresh, epaper PMIC Switched: ");
    Serial.print(fullRefresh3Bit(0) / 1000.0, 3);
    Serial.println("ms");

    // Wait a little bit
    delay(1000);

    // Calculate refresh time of the 3 bit mode, full refresh, epaper PMIC always on.
    Serial.print("3 Bit mode, full refresh, epaper PMIC always on: ");
    Serial.print(fullRefresh3Bit(1) / 1000.0, 3);
    Serial.println("ms");
}

void loop()
{
    // Empty...
}

unsigned long fullRefresh1Bit(uint8_t _leaveSupplyOn)
{
    // Variables for storing timestamps (so we can calculate the refresh time).
    unsigned long time1 = 0;
    unsigned long time2 = 0;

    // Select 1bit mode
    display.selectDisplayMode(INKPLATE_1BIT);

    // Clear everything from the frame buffer.
    display.clearDisplay();

    // Display image for 1 bit mode.
    display.drawImage(image1b, 0, 0, image1b_w, image1b_h);

    // Turn on supply if needed before capturing the time.
    if (_leaveSupplyOn) display.einkOn();
  
    // Capture the time befor refresh
    time1 = micros();

    // Refresh the display.
    display.display(_leaveSupplyOn);

    // Capture the time after refresh.
    time2 = micros();

    // Turn of the epaper power supply.
    if (_leaveSupplyOn) display.einkOff();

    // Return the time.
    return (unsigned long)(time2 - time1);
}

unsigned long fullRefresh3Bit(uint8_t _leaveSupplyOn)
{
    // Variables for storing timestamps (so we can calculate the refresh time).
    unsigned long time1 = 0;
    unsigned long time2 = 0;

    // Select 3bit mode
    display.selectDisplayMode(INKPLATE_3BIT);

    // Clear everything from the frame buffer.
    display.clearDisplay();

    // Display image for 3 bit mode.
    display.drawBitmap3Bit(0, 0, image3b, image3b_w, image3b_h);

    // Turn on supply if needed before capturing the time.
    if (_leaveSupplyOn) display.einkOn();
  
    // Capture the time befor refresh
    time1 = micros();

    // Refresh the display.
    display.display(_leaveSupplyOn);

    // Capture the time after refresh.
    time2 = micros();

    // Turn of the epaper power supply.
    if (_leaveSupplyOn) display.einkOff();

    // Return the time.
    return (unsigned long)(time2 - time1);
}

unsigned long partialRefresh1Bit(uint8_t _leaveSupplyOn)
{
    // Variables for storing timestamps (so we can calculate the refresh time).
    unsigned long time1 = 0;
    unsigned long time2 = 0;

    // Select 1bit mode
    display.selectDisplayMode(INKPLATE_1BIT);

    // Clear everything from the frame buffer.
    display.clearDisplay();

    // Display clear screen on the epaper.
    display.partialUpdate();

    // Display image for 1 bit mode.
    display.drawImage(image1bPartial, 0, 0, image1bPartial_w, image1bPartial_h);

    // Turn on supply if needed before capturing the time.
    if (_leaveSupplyOn) display.einkOn();
  
    // Capture the time befor refresh
    time1 = micros();

    // Refresh the display with partial display.
    display.partialUpdate(0, _leaveSupplyOn);

    // Capture the time after refresh.
    time2 = micros();

    // Turn of the epaper power supply.
    if (_leaveSupplyOn) display.einkOff();

    // Return the time.
    return (unsigned long)(time2 - time1);
}
