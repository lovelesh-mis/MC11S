#include "MC11S_Arduino_Library.h"


// namespace mc11s {


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
    uint8_t nChunk;
    uint16_t nReturned;

    if (!((MC11S_I2C*)device)->_i2cPort)
        return -1;

    int i;                   // counter in loop
    bool bFirstInter = true; // Flag for first iteration - used to send register

    while (numData > 0)
    {
        ((MC11S_I2C*)device)->_i2cPort->beginTransmission(((MC11S_I2C*)device)->deviceAddress);

        if (bFirstInter)
        {
            ((MC11S_I2C*)device)->_i2cPort->write(addr);
            bFirstInter = false;
        }

        if (((MC11S_I2C*)device)->_i2cPort->endTransmission() != 0)
            return -1; // error with the end transmission

        // We're chunking in data - keeping the max chunk to kMaxI2CBufferLength
        nChunk = numData > kChunkSize ? kChunkSize : numData;

        nReturned = ((MC11S_I2C*)device)->_i2cPort->requestFrom((int)((MC11S_I2C*)device)->deviceAddress, (int)nChunk, (int)true);

        // No data returned, no dice
        if (nReturned == 0)
            return -1; // error

        // Copy the retrieved data chunk to the current index in the data segment
        for (i = 0; i < nReturned; i++)
        {
            *data++ = ((MC11S_I2C*)device)->_i2cPort->read();
        }

        // Decrement the amount of data recieved from the overall data request
        // amount
        numData = numData - nReturned;

    } // end while

    return 0; // Success
    // return ((MC11S_I2C*)device)->_i2cBus.readRegisterRegion(((MC11S_I2C*)device)->deviceAddress, addr, data, numData);
}

int32_t MC11S_I2C::write(void* device, uint8_t addr, const uint8_t* data, uint16_t numData)
{
    ((MC11S_I2C*)device)->_i2cPort->beginTransmission(((MC11S_I2C*)device)->deviceAddress);
    ((MC11S_I2C*)device)->_i2cPort->write(addr);
    ((MC11S_I2C*)device)->_i2cPort->write(data, (int)numData);

    return ((MC11S_I2C*)device)->_i2cPort->endTransmission() ? -1 : 0; // -1 = error, 0 = success    
}


// }
