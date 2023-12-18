// UART timeout in milliseconds (from the last received char)
#define UART_TIMEOUT  50ULL

void setup()
{
    // Init serial communication at 115200 bauds.
    Serial.begin(115200);

    // Send welcome message (so we can know that ESP32 and UART / Serial Monitor are alive).
    Serial.println("Code has started!");
}

// Variable that holds timestamp of the last received chah on UART.
unsigned long uartTimer = millis();
void loop()
{
    // Check if you got something on UART.
    if (Serial.available())
    {
        // Capture new timestamp.
        uartTimer = millis();
      
        // Got something? Print message on UART (header)
        Serial.println(" ----- Got something -----");

        // Print it back until there is timeout or there is no more UART data.
        while (Serial.available() && ((unsigned long)(millis() - uartTimer) < UART_TIMEOUT))
        {
            // Got something new on UART?
            if (Serial.available())
            {
                // Capture the timestamp.
                uartTimer = millis();

                // Send back the char.
                Serial.write(Serial.read());
            }
        }

        // Print end (footer)
        Serial.println(" ----- End of message ------");
    }
}
