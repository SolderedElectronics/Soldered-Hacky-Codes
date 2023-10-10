# ESP32 Programmer For STM32 Microcontroller

It allows ESP32 to program STM32 with UART using an STM32 built-in bootloader.

# Usage
- Inside image1.h and image2.h put .bin that needs to be flashed into STM32. This needs to be converted into HEX notation! You can use HxD to open .bin in HEX and Notepad++ find and replace to add "0x" before HEX number.
- Upload this code to the ESP32 board.
- ESP32 GPIO4 is RXD (ESP receives data on this pin) and GPIO5 is TX.
- At start all available commands are shown. Send a number on UART that represents command.
- First command must be 1 - Connect to the STM32
- STM32 must be already in bootloader (BOOT0)

# Connections
ESP32 GPIO4 is UART RX pin and ESP32 GPIO5 is TX. For the STM32 side, check Application Note AN2606.

## Tweeks
- In .h file, you can set start address of the flash, as well as timeouts for the response
- in .ino file you can change Baud tate (but do not change the parity!) and UART pins.

# Notes
- Writing data to the STM32 is not done yet - TODO
