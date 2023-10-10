#include "stm32Prog.h"

STM32Prog::STM32Prog()
{
    // Empty constructor.
}

void STM32Prog::begin(HardwareSerial *_hwSerial)
{
    _progSerial = _hwSerial;
}

void STM32Prog::sendCommand(uint8_t commd)
{
    _progSerial->write(commd);
    _progSerial->write(~commd);
}

uint8_t STM32Prog::erase()
{
    // Variable for response from UART.
    uint8_t _uartBuffer = STM32ERR;

    // Clear out UART RX buffer from any junk data.
    flushRX(STM32PROG_QCK_TIMEOUT);

    // Send erase command.
    sendCommand(STM32ERASE);

    // Get the response from UART.
    if (getFromSerial(&_uartBuffer, sizeof(_uartBuffer), STM32PROG_QCK_TIMEOUT))
    {
        if (_uartBuffer == STM32ACK)
        {
            _progSerial->write(0xFF);
            _progSerial->write(0x00);
        }
        else
        {
            return STM32ERR;
        }
    }

    // Wait until erase has finished.
    if (getFromSerial(&_uartBuffer, sizeof(_uartBuffer), STM32PROG_ERASE_TIMEOUT))
    {
        return _uartBuffer;
    }

    // Otherwise return fail.
    return STM32ERR;
}

uint8_t STM32Prog::eraseExtended()
{
    // Variable for response from UART.
    uint8_t _uartBuffer = STM32ERR;

    // Clear out UART RX buffer from any junk data.
    flushRX(STM32PROG_QCK_TIMEOUT);

    // Send extended erase command.
    sendCommand(STM32ERASEN);

    // Read the response from the UART.
    if (getFromSerial(&_uartBuffer, sizeof(_uartBuffer), STM32PROG_QCK_TIMEOUT))
    {
        if (_uartBuffer == STM32ACK)
        {
            _progSerial->write(0xFF);
            _progSerial->write(0xFF);
            _progSerial->write(0x00);
        }
        else
        {
            return STM32ERR;
        }
    }

    // Wait until erasing has finished.
    if (getFromSerial(&_uartBuffer,  sizeof(_uartBuffer), STM32PROG_ERASE_TIMEOUT))
    {
        return _uartBuffer;
    }

    // Otherwise return fail.
    return STM32ERR;
}

uint8_t STM32Prog::runCommand()
{
    // Variable for response from UART.
    uint8_t _uartBuffer = STM32ERR;

    // Clear out UART RX buffer from any junk data.
    flushRX(STM32PROG_QCK_TIMEOUT);

    // Send STM32 RUN Command.
    sendCommand(STM32RUN);

    // Try to get ACK from UART.
    if (getFromSerial(&_uartBuffer, sizeof(_uartBuffer), STM32PROG_QCK_TIMEOUT))
    {
        if (_uartBuffer == STM32ACK)
        {
            setAddress(STM32STADDR);
            return STM32ACK;
        }
        else
        {
            return STM32ERR;
        }
    }

    // Otherwise return fail.
    return STM32ERR;
}


uint8_t STM32Prog::readChunk(uint8_t *_buffer, unsigned long _readAddress, uint8_t _len)
{
    // Variable for response from UART.
    uint8_t _uartBuffer = STM32ERR;

    // Clear out UART RX buffer from any junk data.
    flushRX(STM32PROG_QCK_TIMEOUT);
    
    // Send read command.
    sendCommand(STM32RD);

    // Check the response from the serial.
    if (getFromSerial(&_uartBuffer, sizeof(_uartBuffer), STM32PROG_QCK_TIMEOUT))
    {
        // Got proper response? Set the read address.
        if (_uartBuffer == STM32ACK)
        {
            if (setAddress(_readAddress) != STM32ACK) return STM32ERR;
        }
        else
        {
            // No response or wrong response? Send error / fail!
            STM32PROG_DBG("missing ACK from STM32");
            return STM32ERR;
        }
    }
    else
    {
        STM32PROG_DBG("missing response from STM32");
    }

    // After address set, get the response from the serial.
    if (!getFromSerial(&_uartBuffer, sizeof(_uartBuffer), STM32PROG_QCK_TIMEOUT))
    {
        if (_uartBuffer == STM32ACK)
        {
            sendCommand(_len); // len + ACK byte6
        }
        else
        {
            return STM32ERR;
        }
    }

    // Get the data from the UART and save them into buffer.
    if (getFromSerial(_buffer, _len + 1, STM32PROG_EXT_TIMEOUT))
    {
        return STM32ACK;
    }

    // Otherwise return fail.
    return STM32ERR;
}

uint8_t STM32Prog::readLarge(uint8_t *_buffer, unsigned long _readAddress, int32_t _len)
{
    // Read chunks of the 255 bytes (since this is the max chunk size of the STM32 UART bootloader).
    // Declare buffer array.
    uint8_t _uartBuffer[256]; // 255 data bytes + 1 ACK byte.

    // Copy start address of the read.
    unsigned long _startAddress = _readAddress;

    // Shift flag (first read do not have 1 byte shift, other ones have)
    uint8_t _shift = 0;

    while (_len > 0)
    {
        // Calculate the chunk size.
        uint8_t _chunkSize = _len>255?255:_len;

        // Try to read the chunk from the STM32. If failed, terminate reading with return error.
        if (readChunk(_uartBuffer, _readAddress, _chunkSize) != STM32ACK) return STM32ERR;

        // Confirm that first byte is ACK. If not, return error.
        if (_uartBuffer[0] != STM32ACK) return STM32ERR;

        // Copy everything to the buffer (skip first byte, since it's ACK)
        memcpy(_buffer + (_readAddress - _startAddress), _uartBuffer + 1, _chunkSize);

        // Calculate the new start address.
        _readAddress += _chunkSize;

        // Decrement the size variable.
        _len -= (_chunkSize);
    }

    return STM32ACK;
}

uint8_t STM32Prog::setAddress(unsigned long addr)
{
    // Variable for the response from UART.
    uint8_t _uartBuffer = STM32ERR;

    // Array for the address.
    uint8_t sendaddr[4];

    // Variable for the checksum.
    uint8_t addcheck = 0;

    // Unsigned long to 4 byte array converion.
    sendaddr[0] = addr >> 24;
    sendaddr[1] = (addr >> 16) & 0xFF;
    sendaddr[2] = (addr >> 8) & 0xFF;
    sendaddr[3] = addr & 0xFF;

    // Clear out UART RX buffer from any junk data.
    flushRX(STM32PROG_QCK_TIMEOUT);

    // Send the data and calculate the checksum.
    for (int i = 0; i <= 3; i++)
    {
        _progSerial->write(sendaddr[i]);
        addcheck ^= sendaddr[i];
    }

    // Send the checksum.
    _progSerial->write(addcheck);

    // Get the response from serial.
    if (getFromSerial(&_uartBuffer, sizeof(_uartBuffer), STM32PROG_QCK_TIMEOUT))
    {
        return _uartBuffer;
    }

    // Otherwise return fail.
    return STM32ERR;
}

uint8_t STM32Prog::sendData(uint8_t *data, uint8_t wrlen)
{
    _progSerial->write(wrlen);
    for (int i = 0; i <= wrlen; i++)
    {
        _progSerial->write(data[i]);
    }
    _progSerial->write(getChecksum(data, wrlen));
    while (!_progSerial->available())
        ;
    return _progSerial->read();
}

uint8_t STM32Prog::getVersion()
{
    unsigned char vsbuf[14];
    sendCommand(STM32GET);
    while (!_progSerial->available())
        ;
    vsbuf[0] = _progSerial->read();
    if (vsbuf[0] != STM32ACK)
        return STM32ERR;
    else
    {
        _progSerial->readBytesUntil(STM32ACK, vsbuf, 14);
        return vsbuf[1];
    }
}

uint16_t STM32Prog::getChipID()
{
    // Variable for storing Chip ID Data.
    int getid = 0;

    // Buffer array for the UART.
    unsigned char _uartBuffer[5];

    // Clear out UART RX buffer from any junk data.
    flushRX(STM32PROG_QCK_TIMEOUT);

    // Send CMD for Chip ID.
    sendCommand(STM32ID);

    // Try to get the resonse.
    if (getFromSerial(_uartBuffer, sizeof(_uartBuffer), STM32PROG_QCK_TIMEOUT))
    {
        // Get ACK and correct size? Nice! Parse it!
        if (_uartBuffer[0] == STM32ACK && _uartBuffer[1] == 1 && _uartBuffer[4] == STM32ACK)
        {
            getid = _uartBuffer[2];
            getid = (getid << 8) + _uartBuffer[3];
            return getid;
        }
        else
        {
            // Got something else? Hmm, thats not good. Return STM32ERR for fail.
            return STM32ERR;
        }
    }

    // Did not get anything? Return STM32ERR for the fail.
    return STM32ERR;
}

uint8_t STM32Prog::getChecksum(unsigned char *data, unsigned char datalen)
{
    unsigned char lendata = datalen;
    for (int i = 0; i <= datalen; i++)
        lendata ^= data[i];
    return lendata;
}

bool STM32Prog::initSTM32(int _retry, unsigned long _delayBetweenRetryMs)
{
    // Variable for storing response from STM32. Set it as STM32 by default.
    uint8_t _rxData = STM32ERR;

    // Clear out UART RX buffer from any junk data.
    flushRX(STM32PROG_QCK_TIMEOUT);

    // Send multiple inits until STM32 reacts to it.
    while (_retry != 0)
    {
        // Send init CMD.
        _progSerial->write(STM32INIT);

        // Wait a little bit.
        delay(10);

        // Check if you did received.
        if (getFromSerial(&_rxData, 1, STM32PROG_LNG_TIMEOUT))
        {
            // Got ACK? Return true as success.
            if (_rxData == STM32ACK) return true;
        }

        // Flush the UART buffer.
        while (_progSerial->available())
        {
            _progSerial->read();
        }

        // Wait a little bit before new retry.
        delay(_delayBetweenRetryMs);

        // Decrement retry variable.
        _retry--;
    }

    // Did not get ACK even after multiple retries?
    // Return false indicating fail.
    return false;
}

bool STM32Prog::getFromSerial(uint8_t *_buffer, int _bufferSize, unsigned long _timeoutMs)
{
    // Counter variable for the buffer.
    int _n = 0;

    // Variable for the timestamp of the last received char from UART.
    // Assime you need to get something from the UARTy so capture current time.
    unsigned long _timeout = millis();

    // Get the data from the serial until the buffer is full or the timeout has occured.
    while (((unsigned long)(millis() - _timeout) < _timeoutMs) && (_n < _bufferSize))
    {
        // Checm if you got something at the UART and you can store that. 
        if (_progSerial->available() && (_n < _bufferSize))
        {
            // Still have space in the buffer? Save the char!
            if (_n < _bufferSize)
            {
                // Save the char in the buffer.
                _buffer[_n++] = _progSerial->read();

                // Update the timeout!
                _timeout = millis();
            }
            else
            {
                // Not enough memory? Drop it!
                _progSerial->read();
            }
        }
    }

    // You did not receive anything? Return an error!
    if (_n == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool STM32Prog::flushRX(unsigned long _timeoutMs)
{
    // Capture the current time.
    unsigned long _timeout = millis();

    while (_progSerial->available() && ((unsigned long)(millis() - _timeout) < _timeoutMs))
    {
        _progSerial->read();
    }

    // If timeout is occured, there is problem with serial communicatoin, return error.
    if (((unsigned long)(millis() - _timeout) >= _timeoutMs)) return false;

    // Otherwise, return success.
    return true;
}