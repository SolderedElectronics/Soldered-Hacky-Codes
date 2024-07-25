#include "Inkplate.h"            //Include Inkplate library to the sketch
Inkplate display(INKPLATE_3BIT); // Create object on Inkplate library and set library to work in monochorme mode

// Defines for outline
#define OUTLINE_COLOR 3
#define OUTLINE_SIZE 3

// Defnies for small squares in the every corner.
#define SQUARE_SIZE 10

void setup()
{
    display.begin();        // Init library (you should call this function ONLY ONCE)
    display.clearDisplay(); // Clear any data that may have been in (software) frame buffer.

    // Draw an thick outline of the actve area of the screen.
    // Top line
    display.fillRect(0, 0, display.width(), OUTLINE_SIZE, OUTLINE_COLOR);

    // Left line
    display.fillRect(0, 0, OUTLINE_SIZE, display.height(), OUTLINE_COLOR);

    // Right line
    display.fillRect(display.width() - OUTLINE_SIZE, 0, OUTLINE_SIZE, display.height(), OUTLINE_COLOR);

    // Bottom line
    display.fillRect(0, display.height() - OUTLINE_SIZE, display.width(), OUTLINE_SIZE, OUTLINE_COLOR);

    // Diagonal lines
    display.drawLine(0, 0, display.width() - 1, display.height() - 1, 0);
    display.drawLine(display.width() - 1, 0, 0, display.height() - 1, 0);

    // Draw squares in every corner of the screen.
    // Now draw 4 small rectangles in all four corners of the screen
    // Top left.
    display.drawRect(0, 0, SQUARE_SIZE, SQUARE_SIZE, 0);
  
    // Top right
    display.drawRect(display.width() - SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE, 0);

    // Bottom left
    display.drawRect(0, display.height() - SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, 0);
    
    // Bottom right
    display.drawRect(display.width() - SQUARE_SIZE, display.height() - SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, 0);

    // Show on screen.
    display.display();
}

void loop()
{
  // Empty...   
}
