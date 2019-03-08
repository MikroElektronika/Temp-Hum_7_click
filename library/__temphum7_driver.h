/*
    __temphum7_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __temphum7_driver.h
@brief    Temp_Hum_7 Driver
@mainpage Temp_Hum_7 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   TEMPHUM7
@brief      Temp_Hum_7 Click Driver
@{

| Global Library Prefix | **TEMPHUM7** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Nov 2018.**      |
| Developer             | **Aleksandar Paunovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _TEMPHUM7_H_
#define _TEMPHUM7_H_

/** 
 * @macro T_TEMPHUM7_P
 * @brief Driver Abstract type 
 */
#define T_TEMPHUM7_P    const uint8_t*

/** @defgroup TEMPHUM7_COMPILE Compilation Config */              /** @{ */

// #define   __TEMPHUM7_DRV_SPI__                            /**<     @macro __TEMPHUM7_DRV_SPI__  @brief SPI driver selector */
   #define   __TEMPHUM7_DRV_I2C__                            /**<     @macro __TEMPHUM7_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __TEMPHUM7_DRV_UART__                           /**<     @macro __TEMPHUM7_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup TEMPHUM7_VAR Variables */                           /** @{ */

/* device address */
extern const uint8_t _TEMPHUM7_DEVICE_ADDRESS;

/* mode */
extern const uint8_t _TEMPHUM7_HOLD_MASTER_MODE;
extern const uint8_t _TEMPHUM7_NOHOLD_MASTER_MODE;
extern const uint8_t _TEMPHUM7_DATA_FROM_PREVIOUS_RH_MEASUREMENT;

/* device registers */
extern const uint8_t _TEMPHUM7_RESET;
extern const uint8_t _TEMPHUM7_WRITE_RHT_USER_REGISTER_1;
extern const uint8_t _TEMPHUM7_READ_RHT_USER_REGISTER_1;
extern const uint8_t _TEMPHUM7_WRITE_HEATER_CONTROL_REGISTER;
extern const uint8_t _TEMPHUM7_READ_HEATER_CONTROL_REGISTER;

/* user register 1 */
extern const uint8_t _TEMPHUM7_RESOLUTION_12_BIT;
extern const uint8_t _TEMPHUM7_RESOLUTION_8_BIT;
extern const uint8_t _TEMPHUM7_RESOLUTION_10_BIT;
extern const uint8_t _TEMPHUM7_RESOLUTION_11_BIT;
extern const uint8_t _TEMPHUM7_HEATER_ENABLE;
extern const uint8_t _TEMPHUM7_HEATER_DISABLE;

/* heater current */
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_3p09;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_9p17;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_15p24;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_21p31;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_27p39;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_33p46;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_39p53;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_45p61;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_51p68;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_57p76;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_63p83;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_69p90;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_75p98;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_82p05;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_88p13;
extern const uint8_t _TEMPHUM7_HEATER_CURRENT_94p20;
                                                                       /** @} */
/** @defgroup TEMPHUM7_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup TEMPHUM7_INIT Driver Initialization */              /** @{ */

#ifdef   __TEMPHUM7_DRV_SPI__
void temphum7_spiDriverInit(T_TEMPHUM7_P gpioObj, T_TEMPHUM7_P spiObj);
#endif
#ifdef   __TEMPHUM7_DRV_I2C__
void temphum7_i2cDriverInit(T_TEMPHUM7_P gpioObj, T_TEMPHUM7_P i2cObj, uint8_t slave);
#endif
#ifdef   __TEMPHUM7_DRV_UART__
void temphum7_uartDriverInit(T_TEMPHUM7_P gpioObj, T_TEMPHUM7_P uartObj);
#endif
                                                                       /** @} */
/** @defgroup TEMPHUM7_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Getting register data
 *
 * @param[in] uint8_t command_  - command
 * @param[in] uint8_t *dataOut_ - data from register(s)
 * @param[in] uint8_t nData_    - number of bytes
 *
 * This function gets nData-bytes from device
 */
void temphum7_getData( uint8_t command_, uint8_t *dataOut_, uint8_t nData_ );

/**
 * @brief Setting register data
 *
 * @param[in] uint8_t command_ - command
 * @param[in] uint8_t dataIn_  - register value
 *
 * This function sets one byte of register data
 */
void temphum7_setData( uint8_t command_, uint8_t dataIn_ );

/**
 * @brief Calculating relative humidity
 *
 * @param[out] float relativeHumidity_ - relative humidity in %
 *
 * This function performs relative humidity measurement and calculates relative humidity
 */
float temphum7_getRelativeHumidity( uint8_t mode_ );

/**
 * @brief Calculating temperature
 *
 * @param[out] float temperature_ - temperature in degrees Celsius
 *
 * This function performs temperature measurement and calculates temperature
 */
float temphum7_getTemperature ( uint8_t mode_ );

/**
 * @brief Reading electronic serial number
 *
 * @param[out] uint8_t *esnBuffer - 14-Byte long electronic serial number
 *
 * This function reads electronic serial number
 */
void temphum7_getElectronicSerialNumber( uint8_t *esnBuffer );

/**
 * @brief Reading firmware revision
 *
 * @param[out] uint8_t fwRevision_ - firmware reviosion register value
 *
 * This function reads device firmware revision
 */
uint8_t temphum7_getFirmwareRevision( void );

/**
 * @brief Calculating heater current
 *
 * @param[out] float heaterCurrent_ - heater current value in mA
 *
 * This function calculates heater current by reading heater control register
 */
float temphum7_getHeaterCurrent( void );

/**
 * @brief Reseting device
 *
 * This function resets device
 */
void temphum7_reset( void );



                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Temp_Hum_7_STM.c
    @example Click_Temp_Hum_7_TIVA.c
    @example Click_Temp_Hum_7_CEC.c
    @example Click_Temp_Hum_7_KINETIS.c
    @example Click_Temp_Hum_7_MSP.c
    @example Click_Temp_Hum_7_PIC.c
    @example Click_Temp_Hum_7_PIC32.c
    @example Click_Temp_Hum_7_DSPIC.c
    @example Click_Temp_Hum_7_AVR.c
    @example Click_Temp_Hum_7_FT90x.c
    @example Click_Temp_Hum_7_STM.mbas
    @example Click_Temp_Hum_7_TIVA.mbas
    @example Click_Temp_Hum_7_CEC.mbas
    @example Click_Temp_Hum_7_KINETIS.mbas
    @example Click_Temp_Hum_7_MSP.mbas
    @example Click_Temp_Hum_7_PIC.mbas
    @example Click_Temp_Hum_7_PIC32.mbas
    @example Click_Temp_Hum_7_DSPIC.mbas
    @example Click_Temp_Hum_7_AVR.mbas
    @example Click_Temp_Hum_7_FT90x.mbas
    @example Click_Temp_Hum_7_STM.mpas
    @example Click_Temp_Hum_7_TIVA.mpas
    @example Click_Temp_Hum_7_CEC.mpas
    @example Click_Temp_Hum_7_KINETIS.mpas
    @example Click_Temp_Hum_7_MSP.mpas
    @example Click_Temp_Hum_7_PIC.mpas
    @example Click_Temp_Hum_7_PIC32.mpas
    @example Click_Temp_Hum_7_DSPIC.mpas
    @example Click_Temp_Hum_7_AVR.mpas
    @example Click_Temp_Hum_7_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __temphum7_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */