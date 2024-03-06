# Soldered Hacky Codes
Useful codes by Soldered Electronics that can speed up the testing and development process.
Use them at your own risk. See the [note](https://github.com/SolderedElectronics/Soldered-Hacky-Codes/blob/main/README.md#%EF%B8%8Fnote%EF%B8%8F) at the bottom!

# Useage of this repo - Submitting
- Every code must be inside its own folder. The folder name must be representative of what the code does. Folder names "Test1234" are **NOT ALLOWED** and will be removed!
- Every code must have a readme
- Code **MUST HAVE** comments (must be well documented!)

Steps:
1. Get the latest version of this repo
2. Make a folder
3. Inside the folder make a readme file
4. Copy your code inside the folder
5. Follow the suggested folder structure if something else than code needs to be added
6. Clean up code (build files, .vscode files should not exist, could use .gitignore file)
7. Make sure that the code is well documented
8. Commit
9. Push
10. Done :)

# README file
Every folder must have readme with:

✅ Details of what specific code does

✅ How to use it and run it

✅ Preferably should be written on how to change some settings

✅ What IDE to use

✅ What type of development board is used

✅ Hardware connections (schematic can be added if needed)

✅ Comments on the limitations of the code, or if something is not working as it should, or something is not done (TODO).

# Other files
If for some reason with a sketch, some other files must be added, make a folder named "extras".
If images are needed, inside "extras" make an "images" folder.

# List
## Arduino_UART_Test
Enables the test of the UART pins by echoing back everything that has been received.

## ESP32_EEPROM_Clean
Simple sketch to clear ESP32 EEPROM.

## ESP32_GPIO_Tester
Simple sketch to test GPIOs of the ESP32 by setting its state or by reading the state of the pin (input only pins).

## ESP32_Programmer_For_STM32
Sketch for programming STM32 by using STM32 HW built-in bootloader with the UART communication.

## I2C_Scanner
Simple Arduino I2C scanner.

## Inkplate_Display_EPD_Active_Area
The sketch shows the edge of the ePaper active area. Useful for checking screen placement in the custom case or to check data corruption/Image shift on the ePaper itself.

## Inkplate_Vcom_Programming
Enables simple VCOM voltage programming in the ePaper PMIC (TPS65186).

Folder structure
```
This repo
    |
    +---[Code_repo1]
            |
            +---[Sketch]
            +---[extras]
                    |
                    +---[images]
                    |      |
                    |       +---image1
                    |       +---image2
                    |
                    +---file1
                    +---file2
                         
```
# ⚠️**NOTE**⚠️
The main purpose of this repo is to help us with development and testing, but we think that these codes can be useful for everyone.

**USE THEM ON YOUR OWN RISK! Soldered Electronic is not responsible for any kind of damage done using any of these codes!**
