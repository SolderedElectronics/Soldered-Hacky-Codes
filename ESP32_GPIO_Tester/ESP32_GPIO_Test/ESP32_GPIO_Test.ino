// GPIO LUT table. Write here pins that are allowed to be tested.
uint8_t gpios[] = {0, 2, 4, 5, 12, 13, 14, 15, 25, 26, 27, 33, 32, 18, 19, 23};

// Input only pins.
uint8_t gpiosInputOnly[] = {34, 35, 36, 39};

void setup()
{
    Serial.begin(115200);
    Serial.println("Send the GPIO number to set it to HIGH state (or read the state for input only pins");

    // Set all GPIOs to LOW.
    clearAllGPIOs();
}

void loop()
{
    // Check if you got something on the UART.
    if (Serial.available())
    {
        // Try to parse it.
        int i = Serial.parseInt();

        // If it's a valid number,  try to change the state on this GPIO.
        if (i != 0)
        {
            // Set all pins to the LOW state.
            clearAllGPIOs();

            // Check if the pin is input only pin.
            if (i < 34)
            {
                // If the pin has output functionality, set the HIGH state.
                Serial.printf("GPIO %d is set to HIGH\r\n", i);
                digitalWrite(i, HIGH);
            }
            else
            {
                // If the pin is input only, read the state of the pin
                Serial.printf("GPIO %d is %d\r\n", i, digitalRead(i));
            }
        }
    }
}

void clearAllGPIOs()
{
    // Set GPIOs with output functionality
    for (int i = 0; i < sizeof(gpios)/sizeof(uint8_t); i++)
    {
        pinMode(gpios[i], OUTPUT);
        digitalWrite(gpios[i], LOW);
    }

    // Set GPIOs with input only functionality
    for (int i = 0; i < sizeof(gpiosInputOnly)/sizeof(uint8_t); i++)
    {
        pinMode(gpiosInputOnly[i], INPUT);
    }
}
