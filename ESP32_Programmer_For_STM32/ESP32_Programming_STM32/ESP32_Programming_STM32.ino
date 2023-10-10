// Include the library for STM32 programming.
#include "stm32Prog.h"

// Include files for the STM32.
// NOTE: Images are .bin files that are converted into HEX with HxD program and Notepad++.
#include "image1.h"
#include "image2.h"

// Create an object for STM32 programmer.
STM32Prog stm;

// Create second serial for STM32 programming.
// Use UART2 for STM32.
HardwareSerial progSerial(2);

void setup()
{
    // Init the Serial Port for debugging.
    Serial.begin(115200);

    // Init Serial Port for STM32 programming.
    // Use GPIO4 of the ESP32 for RXD and GPIO5 for TXD.
    progSerial.begin(115200, SERIAL_8E1, 4, 5);

    // Init the STM32 programming library. Use second serial of the ESP32.
    stm.begin(&progSerial);

    // Send message to the Serial Monitor.
    Serial.println("Code has started!");

    // Print all commands.
    printAllCommands();
}

void loop()
{
    // Wait until you got some command / data on UART.
    if (Serial.available())
    {
        // Got something? Convert it into interger number representing a command,
        int cmd = Serial.parseInt();

        // Check if the number is valid.
        if (cmd != 0)
        {
            processCmd(cmd);
        }
    }
}

void processCmd(int _cmd)
{
    switch(_cmd)
    {
        // Connect command. Must be executed first before anything else!
        case 1:
        {
            if (stm.initSTM32(5, 250ULL))
            {
                Serial.println("Connected to the STM32!");
            }
            else
            {
                Serial.println("Connecting failed!");
            }
            break;
        }
        // Get the chip ID.
        case 2:
        {
            Serial.printf("Got ID 0x%04X\r\n", stm.getChipID());
            break;
        }
        // Run code stored in thr flash memory.
        case 3:
        {
            Serial.printf("Run command %s\r\n", stm.runCommand() == STM32ACK?"ok!":"failed!");
            break;
        }
        // Erase memory. -> Fails for some reason?
        case 4:
        {
            Serial.printf("Erase memory %s\r\n", stm.erase() == STM32ACK?"ok!":"failed!");
            break;
        }
        // Extended memory erase command.
        case 5:
        {
            Serial.printf("Extended memory erase command %s\r\n", stm.eraseExtended() == STM32ACK?"ok!":"failed!");
            break;
        }
        // Read command. Start address = 0x08000000, len = 128 (must be multiple of 4 bytes!).
        case 6:
        {
            // Buffer for the data.
            uint8_t buffer[129]; // 128 data bytes + ACK

            // Clear the array.
            memset(buffer, 0, sizeof(buffer));

            // Send message to the serial.
            Serial.printf("Read command, start address=0x08000000, len = %d\r\n", sizeof(buffer));

            // Try to read the data.
            uint8_t commandResult = stm.readChunk(buffer, 0x08000000, sizeof(buffer) - 1);

            // Check the success. If the read command was succ. print out bytes in HEX.
            if (commandResult == STM32ACK)
            {
                Serial.println("read ok");

                for (int i = 0; i < sizeof(buffer); i++)
                {
                    Serial.printf("0x%02X ", buffer[i]);
                }
            }
            else
            {
                Serial.println("Read command failed!");
            }
            break;
        }
        // Read bigger memory chunk than 255 bytes.
        case 7:
        {
            // Buffer for the data. Store 2048 bytes (no ACK).
            uint8_t readBuffer[2048];

            // Try to read 2048 bytes from the STM32.
            if (stm.readLarge(readBuffer, 0x08000000, sizeof(readBuffer)) == STM32ACK)
            {
                Serial.println("Read large chunk ok");

                // Print out the data on the serial.
                for (int i = 0; i < sizeof(readBuffer); i++)
                {
                    Serial.printf("0x%02X ", readBuffer[i]);
                }
            }
            else
            {
                Serial.println("Read large chunk command failed!");
            }
            break;
        }
        // Not a valid command
        default:
        {
            Serial.println("Unsupported command! Use on of the following commands!");
            printAllCommands();
            break;
        }
    }
}

// Print all commands.
void printAllCommands()
{
    Serial.println("Select command by sending a number (CR and LF doesn't need to be turned on):");
    Serial.println("1 - Connect to the STM32 (send this command before any other command!)");
    Serial.println("2 - Get the chip ID");
    Serial.println("3 - Run / execute the code stored in FLASH memory at default start address. Start address can be changed in stm32Prog.h");
    Serial.println("4 - Erase memory");
    Serial.println("5 - Extended memory erase");
    Serial.println("6 - Read a chunk of the FLASH memory");
    Serial.println("7 - Read larger chunk of the FLASH memory");
}
