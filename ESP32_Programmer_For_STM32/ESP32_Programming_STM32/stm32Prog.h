// Source: https://github.com/csnol/STM32-OTA/blob/master/ESP8266-Src/stm32ota.h

#ifndef _STM32PROG_H_
#define _STM32PROG_H_

// Include main Arduino header file.
#include <Arduino.h>

// Quick timeout for the command reponse
#define STM32PROG_QCK_TIMEOUT   1ULL

// Standard timeout for the command response.
#define STM32PROG_STD_TIMEOUT   5ULL

// Longer timeout for the command response.
#define STM32PROG_LNG_TIMEOUT   50ULL

// Extended timeout for the command response
#define STM32PROG_EXT_TIMEOUT   250UL

// Timeout for the erase commands
#define STM32PROG_ERASE_TIMEOUT 20000ULL

// Debug printf handler
#define STM32PROG_DBG(x) {Serial.printf("[STM32Prog Debug] %s\r\n", x);}

#define STERR        "ERROR"
#define STM32INIT    0x7F // Send Init command
#define STM32ACK     0x79 // return ACK answer
#define STM32NACK    0x1F // return NACK answer
#define STM32GET     0    // get version command
#define STM32GVR     0x01 // get read protection status           never used in here
#define STM32ID      0x02 // get chip ID command
#define STM32RUN     0x21 // Restart and Run programm
#define STM32RD      0x11 // Read flash command                   never used in here
#define STM32WR      0x31 // Write flash command
#define STM32ERASE   0x43 // Erase flash command
#define STM32ERASEN  0x44 // Erase extended flash command
#define STM32WP      0x63 // Write protect command                never used in here
#define STM32WP_NS   0x64 // Write protect no-stretch command     never used in here
#define STM32UNPCTWR 0x73 // Unprotect WR command                 never used in here
#define STM32UW_NS   0x74 // Unprotect write no-stretch command   never used in here
#define STM32RP      0x82 // Read protect command                 never used in here
#define STM32RP_NS   0x83 // Read protect no-stretch command      never used in here
#define STM32UR      0x92 // Unprotect read command               never used in here
#define STM32UR_NS   0x93 // Unprotect read no-stretch command    never used in here

// STM32 codes start address, you can change to other address if use custom bootloader like 0x8002000
#define STM32STADDR 0x8000000
#define STM32ERR    0

class STM32Prog
{
  public:
    STM32Prog();
    void begin(HardwareSerial *_hwSerial);
    void sendCommand(uint8_t commd);
    uint8_t erase();
    uint8_t eraseExtended();
    uint8_t readChunk(uint8_t *_buffer, unsigned long _readAddress, uint8_t _len);
    uint8_t readLarge(uint8_t *_buffer, unsigned long _readAddress, int32_t _len);
    uint8_t setAddress(unsigned long addr);
    uint8_t sendData(uint8_t *data, uint8_t wrlen);
    uint8_t getChecksum(uint8_t *data, uint8_t datalen);
    uint16_t getChipID();
    uint8_t getVersion();
    uint8_t runCommand();
    bool getFromSerial(uint8_t *_buffer, int _bufferSize, unsigned long _timeoutMs);
    bool initSTM32(int _retry, unsigned long _delayBetweenRetryMs);

  private:
    HardwareSerial *_progSerial = NULL;
    bool flushRX(unsigned long _timeoutMs);
};
#endif