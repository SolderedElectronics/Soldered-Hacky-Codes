uint8_t gpios[] = {0, 2, 4, 5, 12, 13, 14, 15, 25, 26, 27, 33, 32, 18, 19, 23};
uint8_t gpiosInputOnly[] = {34, 35, 36, 39};

void setup()
{
    Serial.begin(115200);
    Serial.println("Send the GPIO number to set it to HIGH state (or read the state for input only pins");

    clearAllGPIOs();
}

void loop() {
    if (Serial.available())
    {
        int i = Serial.parseInt();
        if (i != 0)
        {
            clearAllGPIOs();
            if (i < 34)
            {
                Serial.printf("GPIO %d is set to HIGH\r\n", i);
                digitalWrite(i, HIGH);
            }
            else
            {
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
