/*
	MC11S Large-range, dual channel, differential capacitive sensor library for Arduino
	Lovelesh, MIS Electroncis
	
The MIT License (MIT)

Copyright (c) 2015 thingTronics Limited

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

version 0.1
*/

#ifndef __MC11S_Library_H__
#define __MC11S_Library_H__

#include "mc11s_api/mc11s_reg.h"
//#include "sfe_bus.h"


// define a standard i2c address (7 bit) macro

#define MC11S_I2C_ADDRESS 		(MC11S_I2C_ADD >> 1)

class MC11S {
	public:
		int32_t begin();	// Resets the device and sets up for operation
		int32_t isConnected();	// Determined if the device is connected

		int32_t getCh0DataReady(mc11s_drdy_ch0_status_t *drdy);		// Returns if the data of Ch0 is ready to be read or not
		int32_t getCh1DataReady(mc11s_drdy_ch1_status_t *drdy);		// Returns if the data of Ch1 is ready to be read or not 		
        int32_t getAlertStatus(mc11s_alert_status_t *statusVal);	// Returns the status of the device
		int32_t getTrhOfDStatus(mc11s_trh_of_d_status_t *statusVal);		// Returns the status of Data1 threshold overflow bit
		int32_t reset();	// Resets the chip

		int32_t getCh0Data(uint16_t *ch0Val);	// Returns Channel0 raw data
		int32_t getCh1Data(uint16_t *ch1Val);	// Returns Channel1 raw data
        
		int32_t getDeviceID(uint16_t *devId);	// Returns the ID of the MC11S

		int32_t setRcnt(uint16_t val);			// Sets RCNT value
		int32_t getRcnt(uint16_t *val);			// Returns RCNT value

		int32_t setScnt(uint8_t val);			// Sets SCNT Value
		int32_t getScnt(uint8_t *val);			// Returns SCNT Value

		int32_t setFinDiv(mc11s_fin_div_val_t val);	 	// Sets Fin_div
		int32_t getFinDiv(mc11s_fin_div_val_t *val);	// Returns Fin_Div

		
		int32_t setFrefDiv(uint8_t val);		// Sets the Fref_div
		int32_t getFrefDiv(uint8_t *val);		// Returns Fref_div

		int32_t setTrh(uint8_t val);			// Sets Threshold high value
		int32_t getTrh(uint8_t *val);			// Returns Threshold high value

		int32_t setTrl(uint8_t val);			// Sets Threshold low value
		int32_t getTrl(uint8_t *val);			// Returns Threshold low value

		int32_t setRefClkSel(mc11s_ref_clk_sel_status_t val);	// Sets Reference Clock Selector
		int32_t getRefClkSel(mc11s_ref_clk_sel_status_t *val);	// Returns Reference Clock Selector

		int32_t setIntbStatus(mc11s_intb_en_status_t val);		// Sets Interrupt enable bit
		int32_t getIntbStatus(mc11s_intb_en_status_t *val);		// Returns Inerrupt enable bit

		int32_t setIntbMode(mc11s_intb_mode_status_t val);		// Sets Interrupt mode
		int32_t getIntbMode(mc11s_intb_mode_status_t *val);		// Returns Interrupt mode

        int32_t setConvTime(mc11s_conv_time_status_t val);		// Sets Conversion Time
		int32_t getConvTime(mc11s_conv_time_status_t *val);		// Returns Conversion Time

		int32_t setConvMode(mc11s_conv_mode_status_t val);		// Sets Conversion Mode
		int32_t getConvMode(mc11s_conv_mode_status_t *val);		// Returns Conversion Mode

		int32_t setCh0En(mc11s_ch_en_status_t val);				// Sets Channel0 enable bit
		int32_t getCh0En(mc11s_ch_en_status_t *val);			// Returns Channel0 enable bit

		int32_t setCh1En(mc11s_ch_en_status_t val);				// Sets Channel1 enable bit
		int32_t getCh1En(mc11s_ch_en_status_t *val);			// Returns Channel1 enable bit

		int32_t setDriveCurrent(mc11s_drive_i_status_t val);	// Sets Drive current
		int32_t getDriveCurrent(mc11s_drive_i_status_t *val);	// Returns Drive Current


		int32_t setVddSel(mc11s_vdd_sel_status_t val);			// Sets VDD Selection bits
		int32_t getVddSel(mc11s_vdd_sel_status_t *val);			// Returns VDD Selection bits

		int32_t setGlitchFilter(mc11s_glitch_filter_status_t val);	// Sets Glitch Filter Enable bit
		int32_t getGlitchFilter(mc11s_glitch_filter_status_t *val);	// Returns Glitch Filter Enable bit

		int32_t getCapacitance(float *val0, float *val1);		// Calculates Capacitance of Channel 0 & 1
		int32_t getCoef(uint16_t val0, uint16_t val1, float *val2);	// Returns the Coef fix for the given data channel ratio

        int32_t writeFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len); // Write interface definition
        int32_t readFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len); // Read interface defintions

    protected: 
        stmdev_ctx_t sensor;
};

#endif