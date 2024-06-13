#include "MC11S_Arduino_Library.h"


bool MC11S_I2C::begin(uint8_t devAddr, TwoWire& wirePort)
{
    _i2cBus.init(wirePort, false);
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