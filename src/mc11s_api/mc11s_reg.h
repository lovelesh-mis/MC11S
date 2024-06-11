/**
 ******************************************************************************
 * @file    mc11s_reg.h
 * @author  Lovelesh
 * @brief   This file contains all the functions prototypes for the
 *          mc11s_reg.c driver.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MC11S_REGS_H
#define MC11S_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>

/** @addtogroup MC11S
 * @{
 *
 */

/** @defgroup  Endianness definitions
 * @{
 *
 */

#ifndef DRV_BYTE_ORDER
#ifndef __BYTE_ORDER__

#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN    4321

/** if _BYTE_ORDER is not defined, choose the endianness of your architecture
  * by uncommenting the define which fits your platform endianness
  */
//#define DRV_BYTE_ORDER    DRV_BIG_ENDIAN
#define DRV_BYTE_ORDER    DRV_LITTLE_ENDIAN

#else /* defined __BYTE_ORDER__ */

#define DRV_LITTLE_ENDIAN  __ORDER_LITTLE_ENDIAN__
#define DRV_BIG_ENDIAN     __ORDER_BIG_ENDIAN__
#define DRV_BYTE_ORDER     __BYTE_ORDER__

#endif /* __BYTE_ORDER__*/
#endif /* DRV_BYTE_ORDER */

/**
 * @}
 *
 */

/** @defgroup STMicroelectronics sensors common types
 * @{
 *
 */

#ifndef MEMS_SHARED_TYPES
#define MEMS_SHARED_TYPES

typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t bit0 :1;
	uint8_t bit1 :1;
	uint8_t bit2 :1;
	uint8_t bit3 :1;
	uint8_t bit4 :1;
	uint8_t bit5 :1;
	uint8_t bit6 :1;
	uint8_t bit7 :1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t bit7       : 1;
  uint8_t bit6       : 1;
  uint8_t bit5       : 1;
  uint8_t bit4       : 1;
  uint8_t bit3       : 1;
  uint8_t bit2       : 1;
  uint8_t bit1       : 1;
  uint8_t bit0       : 1;
#endif /* DRV_BYTE_ORDER */
} bitwise_t;

#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

typedef int32_t (*stmdev_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*stmdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef void (*stmdev_mdelay_ptr)(uint32_t millisec);

typedef struct
{
  /** Component mandatory fields **/
  stmdev_write_ptr  write_reg;
  stmdev_read_ptr   read_reg;
  /** Component optional fields **/
  stmdev_mdelay_ptr   mdelay;
  /** Customizable optional pointer **/
  void *handle;
} stmdev_ctx_t;

/**
  * @}
  *
  */

#endif /* MEMS_SHARED_TYPES */

#ifndef MEMS_UCF_SHARED_TYPES
#define MEMS_UCF_SHARED_TYPES

/** @defgroup    Generic address-data structure definition
  * @brief       This structure is useful to load a predefined configuration
  *              of a sensor.
  *              You can create a sensor configuration by your own or using
  *              Unico / Unicleo tools available on STMicroelectronics
  *              web site.
  *
  * @{
  *
  */

typedef struct
{
  uint8_t address;
  uint8_t data;
} ucf_line_t;


/**
 * @}
 *
 */

/** @defgroup MC11S_Infos
 * @{
 *
 */

/** I2C Device Address 8 bit format **/
#define MC11S_I2C_ADD			                    0xD0U	// Default Address (if ADDR connected to GND)
// #define MC11S_I2C_ADD		                      0xD2U	// if ADDR connected to VDD
// #define MC11S_I2C_ADD		                      0xD4U	// if ADDR connected to SDA
// #define MC11S_I2C_ADD		                      0xD6U	// if ADDR connected to SCL

/** Device Identification (Who am I) **/
#define STHS34PF80_ID                         0xD

/**
 * @}
 *
 */

/** @defgroup bitfields page main
 * @{
 *
 */

// MC11S Registers
#define MC11S_DATA_CH0_MSB                    0x04U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t data0         : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t data0         : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_data_ch0_msb_t;

#define MC11S_DATA_CH0_LSB                    0x05U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t data0         : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t data0         : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_data_ch0_lsb_t;

#define MC11S_DATA_CH1_MSB                    0x06U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t data1         : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t data1         : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_data_ch1_msb_t;

#define MC11S_DATA_CH1_LSB                    0x07U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t data1         : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t data1         : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_data_ch1_lsb_t;

#define MC11S_RCNT_MSB                        0x0CU
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t rcnt         : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t rcnt         : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_rcnt_msb_t;

#define MC11S_RCNT_LSB                        0x0DU
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t rcnt         : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t rcnt         : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_rcnt_lsb_t;

#define MC11S_SCNT                            0x10U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t scnt         : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t scnt         : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_scnt_t;

#define MC11S_FIN_DIV		                      0x15U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used0     : 4;
  uint8_t fin_div       : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t fin_div       : 4;
  uint8_t not_used0     : 4;
#endif /* DRV_BYTE_ORDER */
} mc11s_fin_div_t;

#define MC11S_FREF_DIV		                    0x16U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fref_div      : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t fref_div      : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_fref_div_t;

#define MC11S_STATUS                          0x18U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t trh_of_d      : 1;
  uint8_t alert         : 1;
  uint8_t not_used0     : 2;
  uint8_t drdy_ch0      : 1;
  uint8_t drdy_ch1      : 1;
  uint8_t not_used1     : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used1     : 2;
  uint8_t drdy_ch1      : 1;
  uint8_t drdy_ch0      : 1;
  uint8_t not_used0     : 2;
  uint8_t alert         : 1;
  uint8_t trh_of_d      : 1;  
#endif /* DRV_BYTE_ORDER */
} mc11s_status_t;

#define MC11S_TRH                             0x1DU
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t trh           : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t trh           : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_trh_t;

#define MC11S_TRL                             0x1EU
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t trl           : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t trl           : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_trl_t;

#define MC11S_CFG                             0x1FU
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sd            : 1;
  uint8_t os            : 1;
  uint8_t cr            : 3;
  uint8_t intb_mode     : 1;
  uint8_t intb_en       : 1;
  uint8_t ref_clk_sel   : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t ref_clk_sel   : 1;
  uint8_t intb_en       : 1;
  uint8_t intb_mode     : 1;
  uint8_t cr            : 3;
  uint8_t os            : 1;
  uint8_t sd            : 1;  
#endif /* DRV_BYTE_ORDER */
} mc11s_cfg_t;

#define MC11S_CH_EN			                      0x21U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used0     : 6;
  uint8_t ch0_en        : 1;
  uint8_t ch1_en        : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t ch1_en        : 1;
  uint8_t ch0_en        : 1;
  uint8_t not_used0     : 6;  
#endif /* DRV_BYTE_ORDER */
} mc11s_ch_en_t;

#define MC11S_RESET			                      0x22U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t reset         : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t reset         : 8;  
#endif /* DRV_BYTE_ORDER */
} mc11s_reset_t;

#define MC11S_DRIVE_I			                    0x25U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t vdd_sel       : 1;
  uint8_t not_used0     : 3;
  uint8_t i0            : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t i0            : 4;
  uint8_t not_used0     : 3;
  uint8_t vdd_sel       : 1;    
#endif /* DRV_BYTE_ORDER */
} mc11s_drive_i_t;

#define MC11S_GLITCH_FILTER_EN                0x33U
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t filter_en     : 1;
  uint8_t not_used0     : 7;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used0     : 7;
  uint8_t filter_en     : 1;
#endif /* DRV_BYTE_ORDER */
} mc11s_glitch_filter_en_t;

#define MC11S_DEVICE_ID_MSB                   0x7EU
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t device_id     : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t device_id     : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_device_id_msb_t;

#define MC11S_DEVICE_ID_LSB                   0x7FU
typedef struct {
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t device_id     : 8;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t device_id     : 8;
#endif /* DRV_BYTE_ORDER */
} mc11s_device_id_lsb_t;

/**
 * @}
 *
 */

typedef union {
  mc11s_data_ch0_msb_t      data_ch0_msb;
  mc11s_data_ch0_lsb_t      data_ch0_msb;
  mc11s_data_ch1_msb_t      data_ch1_msb;
  mc11s_data_ch1_lsb_t      data_ch1_lsb;
  mc11s_rcnt_msb_t          rcnt_msb;
  mc11s_rcnt_lsb_t          rcnt_lsb;
  mc11s_scnt_t              scnt;
  mc11s_fin_div_t           fin_div;
  mc11s_fref_div_t          fref_div;
  mc11s_status_t            status;
  mc11s_trh_t               trh;
  mc11s_trl_t               trl;
  mc11s_cfg_t               cfg;
  mc11s_ch_en_t             ch_en;
  mc11s_reset_t             reset;
  mc11s_drive_i_t           drive_i;
  mc11s_glitch_filter_en_t  glitch_filter_en;
  mc11s_device_id_msb_t     device_id_msb;
  mc11s_device_id_lsb_t     device_id_lsb;
  bitwise_t                 bitwise;
  uint8_t                   byte;
} prefix_lowmain_t;

/**
  * @}
  *
  */

#ifndef __weak
#define __weak __attribute__((weak))
#endif /* __weak */

/*
 * These are the basic platform dependent I/O routines to read
 * and write device registers connected on a standard bus.
 * The driver keeps offering a default implementation based on function
 * pointers to read/write routines for backward compatibility.
 * The default implementation is declared with a __weak directive to
 * allow the final application to overwrite it with a custom implementation.
 */
int32_t mc11s_read_reg(stmdev_ctx_t *ctx, uint8_t reg, uint8_t *data, uint16_t len);

int32_t mc11s_write_reg(stmdev_ctx_t *ctx, uint8_t reg, uint8_t *data, uint16_t len);

int32_t mc11s_device_id_get(stmdev_ctx_t *ctx, uint16_t *val);

int32_t mc11s_data_ch0_get(stmdev_ctx_t *ctx, uint16_t *val);
int32_t mc11s_data_ch1_get(stmdev_ctx_t *ctx, uint16_t *val);

int32_t mc11s_rcnt_set(stmdev_ctx_t *ctx, uint16_t val);
int32_t mc11s_rcnt_get(stmdev_ctx_t *ctx, uint16_t *val);

int32_t mc11s_scnt_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t mc11s_scnt_get(stmdev_ctx_t *ctx, uint8_t *val);

typedef enum {
  MC11S_FIN_DIV_2       = 0x1,
  MC11S_FIN_DIV_4       = 0x2,
  MC11S_FIN_DIV_8       = 0x3,
  MC11S_FIN_DIV_16      = 0x4,
  MC11S_FIN_DIV_32      = 0x5,
  MC11S_FIN_DIV_64      = 0x6,
  MC11S_FIN_DIV_128     = 0x7,
  MC11S_FIN_DIV_256     = 0x8,
} mc11s_fin_div_val_t;
int32_t mc11s_fin_div_set(stmdev_ctx_t *ctx, mc11s_fin_div_val_t val);
int32_t mc11s_fin_div_get(stmdev_ctx_t *ctx, mc11s_fin_div_val_t *val);

int32_t mc11s_fref_div_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t mc11s_fref_div_get(stmdev_ctx_t *ctx, uint8_t *val);

typedef struct {
  uint8_t drdy_ch0      : 1;
} mc11s_drdy_ch0_status_t;
int32_t mc11s_drdy_ch0_status_get(stmdev_ctx_t *ctx, mc11s_drdy_ch0_status_t *val);

typedef struct {
  uint8_t drdy_ch1      : 1;
} mc11s_drdy_ch1_status_t;
int32_t mc11s_drdy_ch1_status_get(stmdev_ctx_t *ctx, mc11s_drdy_ch1_status_t *val);

typedef struct {
  uint8_t alert      : 1;
} mc11s_alert_status_t;
int32_t mc11s_alert_status_get(stmdev_ctx_t *ctx, mc11s_alert_status_t *val);

typedef struct {
  uint8_t trh_of_d      : 1;
} mc11s_trh_of_d_status_t;
int32_t mc11s_trh_of_d_status_get(stmdev_ctx_t *ctx, mc11s_trh_of_d_status_t *val);

int32_t mc11s_tr_set(stmdev_ctx_t *ctx, uint16_t val);
int32_t mc11s_tr_get(stmdev_ctx_t *ctx, uint16_t *val);

typedef enum {
  MC11S_SEL_INT_CLK = 0x0,  MC11s_SEL_EXT_CLK = 0x1,
} mc11s_ref_clk_sel_status_t;
int32_t mc11s_ref_clk_sel_status_set(stmdev_ctx_t *ctx, mc11s_ref_clk_sel_status_t val);
int32_t mc11s_ref_clk_sel_status_get(stmdev_ctx_t *ctx, mc11s_ref_clk_sel_status_t *val);

typedef enum {
  MC11S_INTB_DISABLE = 0x0,  MC11s_INTB_ENABLE = 0x1,
} mc11s_intb_en_status_t;
int32_t mc11s_intb_en_status_set(stmdev_ctx_t *ctx, mc11s_intb_en_status_t val);
int32_t mc11s_intb_en_status_get(stmdev_ctx_t *ctx, mc11s_intb_en_status_t *val);

typedef enum {
  MC11S_INTB_ALARM = 0x0,  MC11s_INTB_CONV = 0x1,
} mc11s_intb_mode_status_t;
int32_t mc11s_intb_mode_status_set(stmdev_ctx_t *ctx, mc11s_intb_mode_status_t val);
int32_t mc11s_intb_mode_status_get(stmdev_ctx_t *ctx, mc11s_intb_mode_status_t *val);

typedef enum {
  MC11S_CONV_60S  = 0x0,
  MC11s_CONV_30S  = 0x1,
  MC11s_CONV_10S  = 0x2,
  MC11s_CONV_5S   = 0x3,
  MC11s_CONV_2S   = 0x4,
  MC11s_CONV_1S   = 0x5,
  MC11s_CONV_0S5  = 0x6,
  MC11s_CONV_0S25 = 0x7,
} mc11s_conv_time_status_t;
int32_t mc11s_conv_time_status_set(stmdev_ctx_t *ctx, mc11s_conv_time_status_t val);
int32_t mc11s_conv_time_status_get(stmdev_ctx_t *ctx, mc11s_conv_time_status_t *val);

typedef enum {
  MC11S_CONT_CONV     = 0x0,
  MC11s_STOP_CONV     = 0x1,
  MC11s_CONT_CONV_RB  = 0x2,
  MC11s_SINGLE_CONV   = 0x3,
} mc11s_conv_mode_status_t;
int32_t mc11s_conv_mode_status_set(stmdev_ctx_t *ctx, mc11s_conv_mode_status_t val);
int32_t mc11s_conv_mode_status_get(stmdev_ctx_t *ctx, mc11s_conv_mode_status_t *val);

typedef enum {
  MC11S_CH0_DISABLE = 0x0,  MC11s_CH0_ENABLE = 0x1,
} mc11s_ch0_en_status_t;
int32_t mc11s_ch0_en_status_set(stmdev_ctx_t *ctx, mc11s_ch0_en_status_t val);
int32_t mc11s_ch0_en_status_get(stmdev_ctx_t *ctx, mc11s_ch0_en_status_t *val);

typedef enum {
  MC11S_CH1_DISABLE = 0x0,  MC11s_CH1_ENABLE = 0x1,
} mc11s_ch1_en_status_t;
int32_t mc11s_ch1_en_status_set(stmdev_ctx_t *ctx, mc11s_ch1_en_status_t val);
int32_t mc11s_ch1_en_status_get(stmdev_ctx_t *ctx, mc11s_ch1_en_status_t *val);

typedef enum {
  MC11S_SW_RESET = 0x7A, MC11S_RESET_COMP = 0x00,
} mc11s_reset_status_t;
int32_t mc11s_reset_set(stmdev_ctx_t *ctx, mc11s_reset_status_t val);
int32_t mc11s_reset_get(stmdev_ctx_t *ctx, mc11s_reset_status_t *val);

typedef enum {
  MC11S_DRIVE_I_200uA  = 0x0,
  MC11s_DRIVE_I_400uA  = 0x1,
  MC11s_DRIVE_I_800uA  = 0x2,
  MC11s_DRIVE_I_1mA6   = 0x3,
  MC11s_DRIVE_I_2mA4   = 0x4,
  MC11s_DRIVE_I_3mA2   = 0x5,
  MC11s_DRIVE_I_3mA2   = 0x6,
  MC11s_DRIVE_I_3mA2   = 0x7,
} mc11s_drive_i_status_t;
int32_t mc11s_drive_i_status_set(stmdev_ctx_t *ctx, mc11s_drive_i_status_t val);
int32_t mc11s_drive_i_status_get(stmdev_ctx_t *ctx, mc11s_drive_i_status_t *val);

typedef enum {
  MC11S_VDD_SEL_2V5_5V5  = 0x0,
  MC11s_VDD_SEL_2V_2V5   = 0x1,
} mc11s_vdd_sel_status_t;
int32_t mc11s_vdd_sel_status_set(stmdev_ctx_t *ctx, mc11s_vdd_sel_status_t val);
int32_t mc11s_vdd_sel_status_get(stmdev_ctx_t *ctx, mc11s_vdd_sel_status_t *val);

typedef enum {
  MC11S_GLITCH_FILTER_DISABLE  = 0x0,
  MC11s_GLITCH_FILTER_ENABLE   = 0x1,
} mc11s_glitch_filter_status_t;
int32_t mc11s_glitch_filter_status_set(stmdev_ctx_t *ctx, mc11s_glitch_filter_status_t val);
int32_t mc11s_glitch_filter_status_get(stmdev_ctx_t *ctx, mc11s_glitch_filter_status_t *val);

#ifdef __cplusplus
}
#endif

#endif /*MC11S_DRIVER_H */