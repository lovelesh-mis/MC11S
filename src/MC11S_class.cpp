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

#include <Arduino.h>
#include "mc11s_class.h"

// #define SPI_READ 0x80

/**
 * @brief  This function begins the examples/communication
 * @retval  Error code (0 -> no Error)
 */
int32_t MC11S::begin() {
	if (isConnected() != 0) {
		return -1;
	}

	reset(); // Reset the device

	// If no errors, return 0
	return 0;
}

/**
 * @brief  	This function determines whether or not the device
 * 		   	is connected to the STHS34PF80. This tests if the device ID
 * 			matches what is expected or not.
 * @retval  Error code (0 -> no Error)
 */
int32_t MC11S::isConnected() {
	uint16_t devId;
	int32_t err = mc11s_device_id_get(&sensor, &devId);

	if (devId != MC11S_ID) {
		return -1;
	}

	return err;
}

/**
 * @brief  			Checks if channel0 data ready flag is high
 * @param	drdy	1 if channel0 conversion completed else 0
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getCh0DataReady(mc11s_drdy_ch0_status_t *drdy) {
	return mc11s_drdy_ch0_status_get(&sensor, drdy);
}

/**
 * @brief  			Checks if channel1 data ready flag is high
 * @param	drdy	1 if channel1 conversion completed else 0
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getCh1DataReady(mc11s_drdy_ch1_status_t *drdy) {
	return mc11s_drdy_ch1_status_get(&sensor, drdy);
} 		

/**
 * @brief  				Checks if Alert flag is high
 * @param	statusVal	1 if alarm triggered else 0
 * @retval  			Error code (0 -> no Error)
 */
int32_t MC11S::getAlertStatus(mc11s_alert_status_t *statusVal) {
	return mc11s_alert_status_get(&sensor, statusVal);
}

/**
 * @brief  				Checks if Threshold Overflow flag is high
 * @param	statusVal	1 if overflow bit is set else 0
 * @retval  			Error code (0 -> no Error)
 */
int32_t MC11S::getTrhOfDStatus(mc11s_trh_of_d_status_t *statusVal) {
	return mc11s_trh_of_d_status_get(&sensor, statusVal);
}

/**
 * @brief  	Resets the device
 * @retval  Error code (0 -> no Error)
 */
int32_t MC11S::reset() {
	return mc11s_reset(&sensor);
}

/**
 * @brief  			Get Channel0 raw data
 * @param	ch0Val	Channel0 data register
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getCh0Data(uint16_t *ch0Val) {
	return mc11s_data_ch0_get(&sensor, ch0Val);
}

/**
 * @brief  			Get Channel1 raw data
 * @param	ch1Val	Channel1 data register
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getCh1Data(uint16_t *ch1Val) {
	return mc11s_data_ch1_get(&sensor, ch1Val);
}

/**
 * @brief  			Get Device ID
 * @param	devId	Device ID
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getDeviceID(uint16_t *devId) {
	return mc11s_device_id_get(&sensor, devId);
}

/**
 * @brief  			Sets RCNT value
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setRcnt(uint16_t val) {
	return mc11s_rcnt_set(&sensor, val);
}

/**
 * @brief  			Gets RCNT value
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getRcnt(uint16_t *val) {
	return mc11s_rcnt_get(&sensor, val);
}

/**
 * @brief  			Sets SCNT value
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setScnt(uint8_t val) {
	return mc11s_scnt_set(&sensor, val);
}

/**
 * @brief  			Gets SCNT value
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getScnt(uint8_t *val) {
	return mc11s_scnt_get(&sensor, val);
}

/**
 * @brief  			Sets Fin_div
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setFinDiv(mc11s_fin_div_val_t val) {
	return mc11s_fin_div_set(&sensor, val);
}

/**
 * @brief  			Gets Fin_div
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getFinDiv(mc11s_fin_div_val_t *val) {
	return mc11s_fin_div_get(&sensor, val);
}

/**
 * @brief  			Sets Fref_div
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setFrefDiv(uint8_t val) {
	return mc11s_fref_div_set(&sensor, val);
}

/**
 * @brief  			Gets Fref_div
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getFrefDiv(uint8_t *val) {
	return mc11s_fref_div_get(&sensor, val);
}

/**
 * @brief  			Sets Threshold high value
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setTrh(uint8_t val) {
	return mc11s_trh_set(&sensor, val);
}

/**
 * @brief  			Gets Threshold high value
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getTrh(uint8_t *val) {
	return mc11s_trh_get(&sensor, val);
}

/**
 * @brief  			Sets Threshold low value
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setTrl(uint8_t val) {
	return mc11s_trl_set(&sensor, val);
}

/**
 * @brief  			Gets Threshold low value
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getTrl(uint8_t *val) {
	return mc11s_trl_get(&sensor, val);
}

/**
 * @brief  			Sets Reference Clock Selector
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setRefClkSel(mc11s_ref_clk_sel_status_t val) {
	return mc11s_ref_clk_sel_status_set(&sensor, val);
}

/**
 * @brief  			Gets Reference Clock Selector
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getRefClkSel(mc11s_ref_clk_sel_status_t *val) {
	return mc11s_ref_clk_sel_status_get(&sensor, val);
}

/**
 * @brief  			Sets Interrupt enable bit
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setIntbStatus(mc11s_intb_en_status_t val) {
	return mc11s_intb_en_status_set(&sensor, val);
}

/**
 * @brief  			Gets Interrupt enable bit
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getIntbStatus(mc11s_intb_en_status_t *val) {
	return mc11s_intb_en_status_get(&sensor, val);
}

/**
 * @brief  			Sets Interrupt mode
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setIntbMode(mc11s_intb_mode_status_t val) {
	return mc11s_intb_mode_status_set(&sensor, val);
}

/**
 * @brief  			Gets Interrupt mode
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getIntbMode(mc11s_intb_mode_status_t *val) {
	return mc11s_intb_mode_status_get(&sensor, val);
}

/**
 * @brief  			Sets Conversion Time
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setConvTime(mc11s_conv_time_status_t val) {
	return mc11s_conv_time_status_set(&sensor, val);
}

/**
 * @brief  			Gets Conversion Time
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getConvTime(mc11s_conv_time_status_t *val) {
	return mc11s_conv_time_status_get(&sensor, val);
}

/**
 * @brief  			Sets Conversion Mode
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setConvMode(mc11s_conv_mode_status_t val) {
	return mc11s_conv_mode_status_set(&sensor, val);
}

/**
 * @brief  			Gets Conversion Mode
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getConvMode(mc11s_conv_mode_status_t *val) {
	return mc11s_conv_mode_status_get(&sensor, val);
}

/**
 * @brief  			Sets Channel0 enable bit
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setCh0En(mc11s_ch_en_status_t val) {
	return mc11s_ch0_en_status_set(&sensor, val);
}

/**
 * @brief  			Gets Channel0 enable bit
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getCh0En(mc11s_ch_en_status_t *val) {
	return mc11s_ch0_en_status_get(&sensor, val);
}

/**
 * @brief  			Sets Channel1 enable bit
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setCh1En(mc11s_ch_en_status_t val) {
	return mc11s_ch1_en_status_set(&sensor, val);
}

/**
 * @brief  			Gets Channel1 enable bit
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getCh1En(mc11s_ch_en_status_t *val) {
	return mc11s_ch1_en_status_get(&sensor, val);
}

/**
 * @brief  			Sets Drive current
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setDriveCurrent(mc11s_drive_i_status_t val) {
	return mc11s_drive_i_status_set(&sensor, val);
}

/**
 * @brief  			Gets Drive current
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getDriveCurrent(mc11s_drive_i_status_t *val) {
	return mc11s_drive_i_status_get(&sensor, val);
}

/**
 * @brief  			Sets VDD Selection bits
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setVddSel(mc11s_vdd_sel_status_t val) {
	return mc11s_vdd_sel_status_set(&sensor, val);
}

/**
 * @brief  			Gets VDD Selection bits
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getVddSel(mc11s_vdd_sel_status_t *val) {
	return mc11s_vdd_sel_status_get(&sensor, val);
}

/**
 * @brief  			Sets Glitch Filter Enable bit
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::setGlitchFilter(mc11s_glitch_filter_status_t val) {
	return mc11s_glitch_filter_status_set(&sensor, val);
}

/**
 * @brief  			Gets Glitch Filter Enable bit
 * @param	val		value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getGlitchFilter(mc11s_glitch_filter_status_t *val) {
	return mc11s_glitch_filter_status_get(&sensor, val);
}

/**
 * @brief  			Calculates capacitance of ref and sensor
 * @param	val0	Channel 0 Capacitor	value
 * @param	val1	Channel 1 Capacitance Value
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getCapacitance(float *val0, float *val1) {
	return mc11s_capacitance_get(&sensor, val0, val1);
}

/**
 * @brief  			Gets the Coef fix for the given ratio of data chaannels
 * @param	val0	Channel0 data
 * @param	val1	Channel1 data
 * @param   val2	Coef fix for the given ratio 
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::getCoef(uint16_t val0, uint16_t val1, float *val2) {
	return mc11s_coef_fix_get(&sensor, val0, val1, val2);
}

/**
 * @brief  			This function writes/sets data to the desired address for the desired number of bytes.
 * @param	addr	register address
 * @param	data	data to be written
 * @param	len		length of the data to be written
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::writeFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len) {
	return mc11s_write_reg(&sensor, addr, data, len);
}

/**
 * @brief  			This function reads data from the desired address for the desired number of bytes.
 * @param	addr	register address
 * @param	data	data to be read
 * @param	len		length of the data to be read
 * @retval  		Error code (0 -> no Error)
 */
int32_t MC11S::readFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len) {
	return mc11s_read_reg(&sensor, addr, data, len);
}
