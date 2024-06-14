#include "MC11S_Arduino_Library.h"


//namespace mc11s {


#define kMaxTransferBuffer 32

// What we use for transfer chunk size
const static uint16_t kChunkSize = kMaxTransferBuffer;

MC11S_I2C::MC11S_I2C(void) : _i2cPort{nullptr}
{

}

bool MC11S_I2C::begin(uint8_t devAddr, TwoWire& wirePort)
{
    // if we don't have a wire port already
    _i2cPort = &wirePort;
    _i2cPort->begin();
    sensor.read_reg = MC11S_I2C::read;
    sensor.write_reg = MC11S_I2C::write;
    // sensor.mdelay = MC11S_I2C::delayMS;
    sensor.handle = this;
    deviceAddress = devAddr;

    // call super class begin -- it returns 0 on no error
    return MC11S::begin() == 0;

}

int32_t MC11S_I2C::read(void* device, uint8_t addr, uint8_t* data, uint16_t numData)
{
    return ((MC11S_I2C*)device)->_i2cBus.readRegisterRegion(((MC11S_I2C*)device)->deviceAddress, addr, data, numData);
}

int32_t MC11S_I2C::write(void* device, uint8_t addr, const uint8_t* data, uint16_t numData)
{
    return ((MC11S_I2C*)device)->_i2cBus.writeRegisterRegion(((MC11S_I2C*)device)->deviceAddress, addr, data, numData);
}

// void MC11S_I2C::delayMS(uint32_t millisec)
// {
//     delay(millisec);
// }

int MC11S_I2C::readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes)
{
    uint8_t nChunk;
    uint16_t nReturned;

    if (!_i2cPort)
        return -1;

    int i;                   // counter in loop
    bool bFirstInter = true; // Flag for first iteration - used to send register

    while (numBytes > 0)
    {
        _i2cPort->beginTransmission(addr);

        if (bFirstInter)
        {
            _i2cPort->write(reg);
            bFirstInter = false;
        }

        if (_i2cPort->endTransmission() != 0)
            return -1; // error with the end transmission

        // We're chunking in data - keeping the max chunk to kMaxI2CBufferLength
        nChunk = numBytes > kChunkSize ? kChunkSize : numBytes;

        nReturned = _i2cPort->requestFrom((int)addr, (int)nChunk, (int)true);

        // No data returned, no dice
        if (nReturned == 0)
            return -1; // error

        // Copy the retrieved data chunk to the current index in the data segment
        for (i = 0; i < nReturned; i++)
        {
            *data++ = _i2cPort->read();
        }

        // Decrement the amount of data recieved from the overall data request
        // amount
        numBytes = numBytes - nReturned;

    } // end while

    return 0; // Success
}

int MC11S_I2C::writeRegisterRegion(uint8_t i2c_address, uint8_t offset, const uint8_t *data, uint16_t length)
{

    _i2cPort->beginTransmission(i2c_address);
    _i2cPort->write(offset);
    _i2cPort->write(data, (int)length);

    return _i2cPort->endTransmission() ? -1 : 0; // -1 = error, 0 = success
}