/******************************************************************************
This file defines all of the constants used in the device library,
along with defining the registers used.

Development environment specifics:
    IDE: Arduino 2.1.0
    Hardware Platform: Arduino Uno
    MC11S Breakout Version: 1.0.0
******************************************************************************/
#ifndef __MC11S_Arduino_Library_H__
#define __MC11S_Arduino_Library_H__


#include "mc11s_class.h"
#include <Wire.h>

// #define DEBUG
#ifdef DEBUG
    #include <Arduino.h>
#endif

class MC11S_I2C : public MC11S 
{
    public: 
        MC11S_I2C(void);
        bool begin(uint8_t devAddr = MC11S_I2C_ADDRESS, TwoWire& wirePort = Wire);
        static int32_t read(void *, uint8_t, uint8_t *, uint16_t);
        static int32_t write(void *, uint8_t, const uint8_t *, uint16_t);
        // static void delayMS(uint32_t millisec);
    private:
        TwoWire *_i2cPort;
        uint8_t deviceAddress;
};

#endif
