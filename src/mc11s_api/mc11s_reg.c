/**
 ******************************************************************************
 * @file    mc11s_reg.c
 * @author  Lovelesh
 * @brief   MC11S driver file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 MIS Electronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "mc11s_reg.h"
#include <Arduino.h>

/**
 * @defgroup  MC11S
 * @brief     This file provides a set of functions needed to drive the
 *            mc11s module.
 * @{
 *
 */

/**
 * @defgroup  Interfaces functions
 * @brief     This section provide a set of functions used to read and
 *            write a generic register of the device.
 *            MANDATORY: return 0 -> no Error.
 * @{
 *
 */

#ifndef __weak
#define __weak __attribute__((weak))
#endif /* __weak */

/**
 * @brief  Read generic device register
 *
 * @param  ctx   communication interface handler.(ptr)
 * @param  reg   first register address to read.
 * @param  data  buffer for data read.(ptr)
 * @param  len   number of consecutive register to read.
 * @retval       interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t __weak mc11s_read_reg(stmdev_ctx_t *ctx, uint8_t reg, uint8_t *data, uint16_t len) {
	int32_t ret;

	ret = ctx->read_reg(ctx->handle, reg, data, len);

	return ret;
}

/**
 * @brief  Write generic device register
 *
 * @param  ctx   communication interface handler.(ptr)
 * @param  reg   first register address to write.
 * @param  data  the buffer contains data to be written.(ptr)
 * @param  len   number of consecutive register to write.
 * @retval       interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t __weak mc11s_write_reg(stmdev_ctx_t *ctx, uint8_t reg, uint8_t *data, uint16_t len) {
	int32_t ret;

	ret = ctx->write_reg(ctx->handle, reg, data, len);

	return ret;
}

/**
 * @}
 *
 */

/**
 * @defgroup Common
 * @brief    Common
 * @{/
 *
 */
/**
 * @brief  Device ID.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      Device ID.
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_device_id_get(stmdev_ctx_t *ctx, uint16_t *val) {
	uint8_t buff[2];
	int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_DEVICE_ID_MSB, &buff[0], 2);
    // MSB is read first and then LSB is read; so swap the buff locations
	*val = (int16_t) buff[0];
	*val = (*val * 256) + (int16_t) buff[1];

	return ret;
}


/**
 * @brief  CH0 sensor data register.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      CH0 data register
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_data_ch0_get(stmdev_ctx_t *ctx, uint16_t *val) {
    uint8_t buff[2];
	int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_DATA_CH0_MSB, &buff[0], 2);
    // MSB is read first and then LSB is read; so swap the buff locations
	*val = (int16_t) buff[0];
	*val = (*val * 256) + (int16_t) buff[1];

	return ret;
}

/**
 * @brief  CH1 sensor data register.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      CH1 data register
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_data_ch1_get(stmdev_ctx_t *ctx, uint16_t *val) {
    uint8_t buff[2];
	int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_DATA_CH1_MSB, &buff[0], 2);
    // MSB is read first and then LSB is read; so swap the buff locations
	*val = (int16_t) buff[0];
	*val = (*val * 256) + (int16_t) buff[1];

	return ret;
}

/**
 * @brief  Counting time configuration register.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      Counting time configuration register
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_rcnt_set(stmdev_ctx_t *ctx, uint16_t val) {
    uint8_t buff[2];
	int32_t ret;

	if ((val & 0x8000U) != 0x0U) {
	    /* threshold values are on 15 bits */
	    return -1;
	}
    // MSB is to be written first and then LSB; so swap the buff locations
	buff[0] = (uint8_t)(val / 256U);
	buff[1] = (uint8_t)(val - (buff[0] * 256U));
	ret += mc11s_write_reg(ctx, MC11S_RCNT_MSB, &buff[0], 2);

	return ret;
}

/**
 * @brief  Counting time configuration register.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      Counting time configuration register
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_rcnt_get(stmdev_ctx_t *ctx, uint16_t *val) {
    uint8_t buff[2];
	int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_RCNT_MSB, &buff[0], 2);
    // MSB is read first and then LSB is read; so swap the buff locations
	*val = (int16_t) buff[0];
	*val = (*val * 256) + (int16_t) buff[1];

	return ret;
}

/**
 * @brief  Setup time configuration register.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      Setup time configuration register
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_scnt_set(stmdev_ctx_t *ctx, uint8_t val) {
	int32_t ret;

	ret = mc11s_write_reg(ctx, MC11S_SCNT, &val, 1);

	return ret;
}

/**
 * @brief  Setup time configuration register.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      Setup time configuration register
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_scnt_get(stmdev_ctx_t *ctx, uint8_t *val) {
	int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_SCNT, val, 1);

	return ret;
}

/**
 * @brief  Select Input Frequency Divider.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      DIV_2, DIV_4, DIV_8, DIV_16, DIV_32, DIV_64, DIV_128, DIV_256
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_fin_div_set(stmdev_ctx_t *ctx, mc11s_fin_div_val_t val) {
    mc11s_fin_div_t fin_div_val;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_FIN_DIV, (uint8_t*) &fin_div_val, 1);

    if (ret == 0) {
        fin_div_val.fin_div = ((uint8_t) val & 0xFU);
        ret = mc11s_write_reg(ctx, MC11S_FIN_DIV, (uint8_t*) &fin_div_val, 1); 
    }

    return ret;
}

/**
 * @brief  Select Input Frequency Divider.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      DIV_2, DIV_4, DIV_8, DIV_16, DIV_32, DIV_64, DIV_128, DIV_256
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_fin_div_get(stmdev_ctx_t *ctx, mc11s_fin_div_val_t *val) {
    mc11s_fin_div_t fin_div_val;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_FIN_DIV, (uint8_t*) &fin_div_val, 1);

    switch(fin_div_val.fin_div) {
        case MC11S_FIN_DIV_2:
            *val = MC11S_FIN_DIV_2;
            break;
        
        case MC11S_FIN_DIV_4:
            *val = MC11S_FIN_DIV_4;
            break;

        case MC11S_FIN_DIV_8:
            *val = MC11S_FIN_DIV_8;
            break;

        case MC11S_FIN_DIV_16:
            *val = MC11S_FIN_DIV_16;
            break;

        case MC11S_FIN_DIV_32:
            *val = MC11S_FIN_DIV_32;
            break;    

        case MC11S_FIN_DIV_64:
            *val = MC11S_FIN_DIV_64;
            break;

        case MC11S_FIN_DIV_128:
            *val = MC11S_FIN_DIV_128;
            break;

        case MC11S_FIN_DIV_256:
            *val = MC11S_FIN_DIV_256;
            break;
        
        default:
            *val = MC11S_FIN_DIV_8;
            break;
    }

    return ret;
}

/**
 * @brief  Select Reference Frequency Divider.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      0 to 255 (FREF_DIV + 1)
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_fref_div_set(stmdev_ctx_t *ctx, uint8_t val) {
    int32_t ret;

	ret = mc11s_write_reg(ctx, MC11S_FREF_DIV, &val, 1);

	return ret;
}

/**
 * @brief  Select Reference Frequency Divider.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      0 to 255 (FREF_DIV + 1)
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_fref_div_get(stmdev_ctx_t *ctx, uint8_t *val) {
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_FREF_DIV, val, 1);

	return ret;
}

/**
 * @brief  Status of Channel0 drdy.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if channel0 conversion completed else 0
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_drdy_ch0_status_get(stmdev_ctx_t *ctx, mc11s_drdy_ch0_status_t *val) {
     mc11s_status_t status;
     int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_STATUS, (uint8_t*) &status, 1);

    val->drdy_ch0 = status.drdy_ch0;

	return ret;
}

/**
 * @brief  Status of Channel1 drdy.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if channel1 conversion completed else 0
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_drdy_ch1_status_get(stmdev_ctx_t *ctx, mc11s_drdy_ch1_status_t *val) {
     mc11s_status_t status;
     int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_STATUS, (uint8_t*) &status, 1);

    val->drdy_ch1 = status.drdy_ch1;

	return ret;
}

/**
 * @brief  Status of Alert bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if alarm triggered else 0
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_alert_status_get(stmdev_ctx_t *ctx, mc11s_alert_status_t *val) {
     mc11s_status_t status;
     int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_STATUS, (uint8_t*) &status, 1);

    val->alert = status.alert;

	return ret;
}

/**
 * @brief  Status of Data1 Threshold overflow bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if overflow bit is set else 0
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_trh_of_d_status_get(stmdev_ctx_t *ctx, mc11s_trh_of_d_status_t *val) {
     mc11s_status_t status;
     int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_STATUS, (uint8_t*) &status, 1);

    val->trh_of_d = status.trh_of_d;

	return ret;
}

/**
 * @brief  Alarm Trigger Threshold register.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      Alarm trigger threshold register (0x40 * DATA_D0 / DATA_D1 > TRH)
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_trh_set(stmdev_ctx_t *ctx, uint8_t val) {
	int32_t ret;

	ret = mc11s_write_reg(ctx, MC11S_TRH, &val, 1);

	return ret;
}

/**
 * @brief  Alarm Trigger Threshold register.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      Alarm trigger threshold register (0x40 * DATA_D0 / DATA_D1 > TRH)
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_trh_get(stmdev_ctx_t *ctx, uint8_t *val) {
	int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_TRH, val, 1);

	return ret;
}

/**
 * @brief  Alarm Release Threshold register.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      Alarm release threshold register (0x40 * DATA_D0 / DATA_D1 < TRL)
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_trl_set(stmdev_ctx_t *ctx, uint8_t val) {
	int32_t ret;

	ret = mc11s_write_reg(ctx, MC11S_TRL, &val, 1);

	return ret;
}

/**
 * @brief  Alarm Release Threshold register.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      Alarm release threshold register (0x40 * DATA_D0 / DATA_D1 < TRL)
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_trl_get(stmdev_ctx_t *ctx, uint8_t *val) {
	int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_TRL, val, 1);

	return ret;
}

/**
 * @brief  Status of Reference Clock Selector bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if external clock is selected, 0 if internal clock is selected
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_ref_clk_sel_status_set(stmdev_ctx_t *ctx, mc11s_ref_clk_sel_status_t val) {
    mc11s_cfg_t status;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1);

    if (ret == 0) {
        status.ref_clk_sel = (uint8_t) val;
        ret = mc11s_write_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1); 
    }

    return ret;
    
}

/**
 * @brief  Status of Reference Clock Selector bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if external clock is selected, 0 if internal clock is selected
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_ref_clk_sel_status_get(stmdev_ctx_t *ctx, mc11s_ref_clk_sel_status_t *val) {
    mc11s_cfg_t status;
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1);

    switch (status.ref_clk_sel) {
        case MC11S_SEL_INT_CLK:
            *val = MC11S_SEL_INT_CLK;
            break;

        case MC11S_SEL_EXT_CLK:
            *val = MC11S_SEL_EXT_CLK;
            break;
    
        default:
            *val = MC11S_SEL_INT_CLK;
            break;
    }

	return ret;
}


/**
 * @brief  Status of Interrupt Output Enable bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if interrupt is mapped to alarm flag or conversion completion flag, 0 if it doesnot output flag bit
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_intb_en_status_set(stmdev_ctx_t *ctx, mc11s_intb_en_status_t val) {
    mc11s_cfg_t status;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1);

    if (ret == 0) {
        status.intb_en = (uint8_t) val;
        ret = mc11s_write_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1); 
    }

    return ret;
    
}

/**
 * @brief  Status of Interrupt Output Enable bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if interrupt is mapped to alarm flag or conversion completion flag, 0 if it doesnot output flag bit
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_intb_en_status_get(stmdev_ctx_t *ctx, mc11s_intb_en_status_t *val) {
    mc11s_cfg_t status;
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1);

    switch (status.intb_en) {
        case MC11S_INTB_DISABLE:
            *val = MC11S_INTB_DISABLE;
            break;

        case MC11S_INTB_ENABLE:
            *val = MC11S_INTB_ENABLE;
            break;
    
        default:
            *val = MC11S_INTB_ENABLE;
            break;
    }

	return ret;
}

/**
 * @brief  Status of Interrupt Mode bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if interrupt is mapped to alarm flag, 0 if interrupt mapped to conversion completion flag
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_intb_mode_status_set(stmdev_ctx_t *ctx, mc11s_intb_mode_status_t val) {
    mc11s_cfg_t status;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1);

    if (ret == 0) {
        status.intb_mode = (uint8_t) val;
        ret = mc11s_write_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1); 
    }

    return ret;
    
}

/**
 * @brief  Status of Interrupt Mode bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if interrupt is mapped to alarm flag, 0 if interrupt mapped to conversion completion flag
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_intb_mode_status_get(stmdev_ctx_t *ctx, mc11s_intb_mode_status_t *val) {
    mc11s_cfg_t status;
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1);

    switch (status.intb_mode) {
        case MC11S_INTB_ALARM:
            *val = MC11S_INTB_ALARM;
            break;

        case MC11S_INTB_CONV:
            *val = MC11S_INTB_CONV;
            break;
    
        default:
            *val = MC11S_INTB_ALARM;
            break;
    }

	return ret;
}

/**
 * @brief  Status of Conversion time bits.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      CONV_60S, CONV_30S, CONV_10S, CONV_5S, CONV_2S, CONV_1S, CONV_0S5, CONV_0S25
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_conv_time_status_set(stmdev_ctx_t *ctx, mc11s_conv_time_status_t val) {
    mc11s_cfg_t status;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1);

    if (ret == 0) {
        status.cr = ((uint8_t) val & 0x7U);
        ret = mc11s_write_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1); 
    }

    return ret;
    
}

/**
 * @brief  Status of Conversion time bits.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      CONV_60S, CONV_30S, CONV_10S, CONV_5S, CONV_2S, CONV_1S, CONV_0S5, CONV_0S25
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_conv_time_status_get(stmdev_ctx_t *ctx, mc11s_conv_time_status_t *val) {
    mc11s_cfg_t status;
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1);

    switch (status.cr) {
        case MC11S_CONV_60S:
            *val = MC11S_CONV_60S;
            break;

        case MC11S_CONV_30S:
            *val = MC11S_CONV_30S;
            break;
    
        case MC11S_CONV_10S:
            *val = MC11S_CONV_10S;
            break;

        case MC11S_CONV_5S:
            *val = MC11S_CONV_5S;
            break;

        case MC11S_CONV_2S:
            *val = MC11S_CONV_2S;
            break;

        case MC11S_CONV_1S:
            *val = MC11S_CONV_1S;
            break;

        case MC11S_CONV_0S5:
            *val = MC11S_CONV_0S5;
            break;

        case MC11S_CONV_0S25:
            *val = MC11S_CONV_0S25;
            break;

        default:
            *val = MC11S_CONV_1S;
            break;
    }

	return ret;
}

/**
 * @brief  Status of Channel Conversion Mode bits.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      CONT_CONV, STOP_CONV, CONT_CONV_RB, SINGLE_CONV
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_conv_mode_status_set(stmdev_ctx_t *ctx, mc11s_conv_mode_status_t val) {
    mc11s_cfg_t status;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1);

    if (ret == 0) {
        status.os_sd = ((uint8_t) val & 0x3U);
        ret = mc11s_write_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1); 
    }

    return ret;
    
}

/**
 * @brief  Status of Channel Conversion Mode bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      CONT_CONV, STOP_CONV, CONT_CONV_RB, SINGLE_CONV
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_conv_mode_status_get(stmdev_ctx_t *ctx, mc11s_conv_mode_status_t *val) {
    mc11s_cfg_t status;
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_CFG, (uint8_t*) &status, 1);

    switch (status.os_sd) {
        case MC11S_CONT_CONV:
            *val = MC11S_CONT_CONV;
            break;

        case MC11S_STOP_CONV:
            *val = MC11S_STOP_CONV;
            break;
    
        case MC11S_CONT_CONV_RB:
            *val = MC11S_CONT_CONV_RB;
            break;

        case MC11S_SINGLE_CONV:
            *val = MC11S_SINGLE_CONV;
            break;

        default:
            *val = MC11S_CONT_CONV;
            break;
    }

	return ret;
}

/**
 * @brief  Status of Channel0 enable bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if channel0 is enabled else 0
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_ch0_en_status_set(stmdev_ctx_t *ctx, mc11s_ch_en_status_t val) {
    mc11s_ch_en_t status;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_CH_EN, (uint8_t*) &status, 1);

    if (ret == 0) {
        status.ch0_en = (uint8_t) val;
        ret = mc11s_write_reg(ctx, MC11S_CH_EN, (uint8_t*) &status, 1); 
    }

    return ret;
    
}

/**
 * @brief  Status of Channel0 enable bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if channel0 is enabled else 0
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_ch0_en_status_get(stmdev_ctx_t *ctx, mc11s_ch_en_status_t *val) {
    mc11s_ch_en_t status;
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_CH_EN, (uint8_t*) &status, 1);

    switch (status.ch0_en) {
        case MC11S_CH_DISABLE:
            *val = MC11S_CH_DISABLE;
            break;

        case MC11S_CH_ENABLE:
            *val = MC11S_CH_ENABLE;
            break;
    
        default:
            *val = MC11S_CH_ENABLE;
            break;
    }

	return ret;
}

/**
 * @brief  Status of Channel1 enable bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if channel1 is enabled else 0
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_ch1_en_status_set(stmdev_ctx_t *ctx, mc11s_ch_en_status_t val) {
    mc11s_ch_en_t status;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_CH_EN, (uint8_t*) &status, 1);

    if (ret == 0) {
        status.ch1_en = (uint8_t) val;
        ret = mc11s_write_reg(ctx, MC11S_CH_EN, (uint8_t*) &status, 1); 
    }

    return ret;
    
}

/**
 * @brief  Status of Channel1 enable bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if channel1 is enabled else 0
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_ch1_en_status_get(stmdev_ctx_t *ctx, mc11s_ch_en_status_t *val) {
    mc11s_ch_en_t status;
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_CH_EN, (uint8_t*) &status, 1);

    switch (status.ch1_en) {
        case MC11S_CH_DISABLE:
            *val = MC11S_CH_DISABLE;
            break;

        case MC11S_CH_ENABLE:
            *val = MC11S_CH_ENABLE;
            break;
    
        default:
            *val = MC11S_CH_ENABLE;
            break;
    }

	return ret;
}

/**
 * @brief  Reset Device.
 *
 * @param  ctx      read / write interface definitions
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_reset(stmdev_ctx_t *ctx) {
	uint8_t tmp;
    int32_t ret;

    tmp = MC11S_SW_RESET;
	ret = mc11s_write_reg(ctx, MC11S_RESET, &tmp, 1);

	return ret;
}

/**
 * @brief  Status of Drive current bits.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      DRIVE_I_200uA, DRIVE_I_400uA, DRIVE_I_800uA, DRIVE_I_1mA6, DRIVE_I_2mA4, DRIVE_I_3mA2_1, DRIVE_I_3mA2_2, DRIVE_I_3mA2_3
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_drive_i_status_set(stmdev_ctx_t *ctx, mc11s_drive_i_status_t val) {
    mc11s_drive_i_t status;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_DRIVE_I, (uint8_t*) &status, 1);

    if (ret == 0) {
        status.i0 = ((uint8_t) val & 0xFU);
        ret = mc11s_write_reg(ctx, MC11S_DRIVE_I, (uint8_t*) &status, 1); 
    }

    return ret;
    
}

/**
 * @brief  Status of Drive current bits.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      DRIVE_I_200uA, DRIVE_I_400uA, DRIVE_I_800uA, DRIVE_I_1mA6, DRIVE_I_2mA4, DRIVE_I_3mA2_1, DRIVE_I_3mA2_2, DRIVE_I_3mA2_3
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_drive_i_status_get(stmdev_ctx_t *ctx, mc11s_drive_i_status_t *val) {
    mc11s_drive_i_t status;
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_DRIVE_I, (uint8_t*) &status, 1);

    switch (status.i0) {
        case MC11S_DRIVE_I_200uA:
            *val = MC11S_DRIVE_I_200uA;
            break;

        case MC11S_DRIVE_I_400uA:
            *val = MC11S_DRIVE_I_400uA;
            break;
    
        case MC11S_DRIVE_I_800uA:
            *val = MC11S_DRIVE_I_800uA;
            break;

        case MC11S_DRIVE_I_1mA6:
            *val = MC11S_DRIVE_I_1mA6;
            break;

        case MC11S_DRIVE_I_3mA2_1:
        case MC11S_DRIVE_I_3mA2_2:
        case MC11S_DRIVE_I_3mA2_3:
            *val = MC11S_DRIVE_I_3mA2_1;
            break;

        default:
            *val = MC11S_DRIVE_I_200uA;
            break;
    }

	return ret;
}

/**
 * @brief  Status of VDD selection bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      VDD_SEL_2V5_5V5, VDD_SEL_2V_2V5
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_vdd_sel_status_set(stmdev_ctx_t *ctx, mc11s_vdd_sel_status_t val) {
    mc11s_drive_i_t status;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_DRIVE_I, (uint8_t*) &status, 1);

    if (ret == 0) {
        status.vdd_sel = (uint8_t) val;
        ret = mc11s_write_reg(ctx, MC11S_DRIVE_I, (uint8_t*) &status, 1); 
    }

    return ret;
    
}

/**
 * @brief  Status of VDD seection bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      VDD_SEL_2V5_5V5, VDD_SEL_2V_2V5
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_vdd_sel_status_get(stmdev_ctx_t *ctx, mc11s_vdd_sel_status_t *val) {
    mc11s_drive_i_t status;
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_DRIVE_I, (uint8_t*) &status, 1);

    switch (status.vdd_sel) {
        case MC11S_VDD_SEL_2V5_5V5:
            *val = MC11S_VDD_SEL_2V5_5V5;
            break;

        case MC11S_VDD_SEL_2V_2V5:
            *val = MC11S_VDD_SEL_2V_2V5;
            break;
    
        default:
            *val = MC11S_VDD_SEL_2V5_5V5;
            break;
    }

	return ret;
}

/**
 * @brief  Status of Glitch Filter enable bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if glitch filter is enabled else 0
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_glitch_filter_status_set(stmdev_ctx_t *ctx, mc11s_glitch_filter_status_t val) {
    mc11s_glitch_filter_en_t status;
    int32_t ret;

    ret = mc11s_read_reg(ctx, MC11S_GLITCH_FILTER_EN, (uint8_t*) &status, 1);

    if (ret == 0) {
        status.filter_en = (uint8_t) val;
        ret = mc11s_write_reg(ctx, MC11S_GLITCH_FILTER_EN, (uint8_t*) &status, 1); 
    }

    return ret;
    
}

/**
 * @brief  Status of Glitch Filter enable bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @param  val      1 if glitch filter is enabled else 0
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_glitch_filter_status_get(stmdev_ctx_t *ctx, mc11s_glitch_filter_status_t *val) {
    mc11s_glitch_filter_en_t status;
    int32_t ret;

	ret = mc11s_read_reg(ctx, MC11S_GLITCH_FILTER_EN, (uint8_t*) &status, 1);

    switch (status.filter_en) {
        case MC11S_GLITCH_FILTER_DISABLE:
            *val = MC11S_GLITCH_FILTER_DISABLE;
            break;

        case MC11S_GLITCH_FILTER_ENABLE:
            *val = MC11S_GLITCH_FILTER_ENABLE;
            break;
    
        default:
            *val = MC11S_GLITCH_FILTER_ENABLE;
            break;
    }

	return ret;
}

/**
 * @brief  Calculate capacitance of ref and sensor.
 *
 * @param  ctx      read / write interface definitions
 * @param  C_ch0    Capacitance of channel 0
 * @param  C_ch1    Capacitance of channel 1
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_capacitance_get(stmdev_ctx_t *ctx, float *C_ch0, float *C_ch1) {
    // C(sensor): 8.670 pf F1(ref):26.036 MHz F2(sensor):23.682 MHz VBE: 626.08 mV
    int32_t ret;

    mc11s_conv_mode_status_t conv_mode_val;
    // Step 1: Get Conversion mode and Stop Conversion 
    ret = mc11s_conv_mode_status_get(ctx, &conv_mode_val);
    ret += mc11s_conv_mode_status_set(ctx, MC11S_STOP_CONV);

    // Step 2a: get ch0 & ch1 data
    uint16_t data_ch0, data_ch1;

    ret += mc11s_data_ch0_get(ctx, &data_ch0);

    ret += mc11s_data_ch1_get(ctx, &data_ch1);


    // Step 2b: get Fin_div
    //uint16_t Fin_div;
    mc11s_fin_div_val_t Fin_div_val;
    ret += mc11s_fin_div_get(ctx, &Fin_div_val);

    if (Fin_div_val > MC11S_FIN_DIV_256)
        Fin_div_val = MC11S_FIN_DIV_256;

    //Fin_div = 2 ^ Fin_div_val;

    // Step 2c: get Fclk
    uint32_t Fclk = 2400000;    // 2.4 MHz CLK

    // Step 2d: get Fref_div
    uint16_t Fref_div;

    ret += mc11s_fref_div_get(ctx, (uint8_t*) &Fref_div);

    //Fref_div = Fref_div + 1;    // Fref value from 1 to 256

    // Step 2e: get RCNT
    uint16_t rcnt;

    ret += mc11s_rcnt_get(ctx, &rcnt);

    // Step 2f: get Idrv
    uint16_t Idrv;
    mc11s_drive_i_status_t drive_i;

    ret += mc11s_drive_i_status_get(ctx, &drive_i);

    switch (drive_i) {
        case MC11S_DRIVE_I_200uA:
            Idrv = 200;
            break;
        
        case MC11S_DRIVE_I_400uA:
            Idrv = 400;
            break;

        case MC11S_DRIVE_I_800uA:
            Idrv = 800;
            break;

        case MC11S_DRIVE_I_1mA6:
            Idrv = 1600;
            break;

        case MC11S_DRIVE_I_2mA4:
            Idrv = 2400;
            break;
            
        case MC11S_DRIVE_I_3mA2_1:
        case MC11S_DRIVE_I_3mA2_2:
        case MC11S_DRIVE_I_3mA2_3:
            Idrv = 3200;
            break;

        default:
            Idrv = 0;
            break;
    }

    // Step 3: Calculate Channel 1 capacitance
    // C = k * Idrv /(data_chx * Fin_div * (Fclk /(Fref_div + 1))/ RCNT)
    *C_ch1 = (float) (K * Idrv / (data_ch1 * (2 ^ Fin_div_val) * (Fclk / (Fref_div + 1)) / rcnt));

    // Step 3a: Calculate Channel 0 capacitance
    //*Csensor = (float) (K * Idrv / (data_ch0 * (2 ^ Fin_div_val) * (Fclk / (Fref_div + 1)) / rcnt));

    // Step 4: Get Coef fix for the values
    float Coef_fix;
    ret += mc11s_coef_fix_get(ctx, data_ch0, data_ch1, &Coef_fix);

    // Step 5: Calculate Channel 0 capacitance
    *C_ch0 = (data_ch1 / data_ch0) * (*C_ch1) * Coef_fix;

    // Step 6: Set the conversion mode to previous value
    ret += mc11s_conv_mode_status_set(ctx, conv_mode_val);

    return ret;
}

/**
 * @brief  Return the value of Coef_fix for a given ratio of Data_Ch1 / Data_Ch0
 *
 * @param  ctx      read / write interface definitions
 * @param  val0     Channel0 Data Register value
 * @param  val1     Channel1 Data Register value
 * @param  Coef_fix Coef_fix value based on the table in the datasheet
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mc11s_coef_fix_get(stmdev_ctx_t *ctx, uint16_t val0, uint16_t val1, float *Coef_fix) {
    float ratio;
    int32_t ret;

    ratio = (float) val1 / val0;

    if (ratio >= 0.529 && ratio < 0.623) {
        *Coef_fix = 0.946;
    } else if (ratio >= 0.623 && ratio < 0.717) {
        *Coef_fix = 0.963;
    } else if (ratio >= 0.717 && ratio < 0.812) {
        *Coef_fix = 0.976;
    } else if (ratio >= 0.812 && ratio < 0.906) {
        *Coef_fix = 0.985;
    } else if (ratio >= 0.906 && ratio < 1.000) {
        *Coef_fix = 0.993;
    } else if (ratio >= 1.000 && ratio < 1.094) {
        *Coef_fix = 1.000;
    } else if (ratio >= 1.094 && ratio < 1.187) {
        *Coef_fix = 1.005;
    } else if (ratio >= 1.187 && ratio < 1.281) {
        *Coef_fix = 1.011;
    } else if (ratio >= 1.281 && ratio < 1.373) {
        *Coef_fix = 1.015;
    } else if (ratio >= 1.373 && ratio < 1.466) {
        *Coef_fix = 1.019;
    } else if (ratio >= 1.466) {
        *Coef_fix = 1.023;
    } else
        *Coef_fix = 1.000;

    return ret;
}
/**
 * @}
 *
 */
