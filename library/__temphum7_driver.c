/*
    __temphum7_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__temphum7_driver.h"
#include "__temphum7_hal.c"

/* ------------------------------------------------------------------- MACROS */

/* device address */
const uint8_t _TEMPHUM7_DEVICE_ADDRESS                    = 0x40;

/* mode */
const uint8_t _TEMPHUM7_HOLD_MASTER_MODE                  = 0x00;
const uint8_t _TEMPHUM7_NOHOLD_MASTER_MODE                = 0x01;
const uint8_t _TEMPHUM7_DATA_FROM_PREVIOUS_RH_MEASUREMENT = 0x02;

/* device registers */
const uint8_t _TEMPHUM7_RESET                             = 0xFE;
const uint8_t _TEMPHUM7_WRITE_RHT_USER_REGISTER_1         = 0xE6;
const uint8_t _TEMPHUM7_READ_RHT_USER_REGISTER_1          = 0xE7;
const uint8_t _TEMPHUM7_WRITE_HEATER_CONTROL_REGISTER     = 0x51;
const uint8_t _TEMPHUM7_READ_HEATER_CONTROL_REGISTER      = 0x11;

/* user register 1 */
const uint8_t _TEMPHUM7_RESOLUTION_12_BIT                 = 0x00;
const uint8_t _TEMPHUM7_RESOLUTION_8_BIT                  = 0x01;
const uint8_t _TEMPHUM7_RESOLUTION_10_BIT                 = 0x80;
const uint8_t _TEMPHUM7_RESOLUTION_11_BIT                 = 0x81;
const uint8_t _TEMPHUM7_HEATER_ENABLE                     = 0x04;
const uint8_t _TEMPHUM7_HEATER_DISABLE                    = 0x00;

/* heater current */
const uint8_t _TEMPHUM7_HEATER_CURRENT_3p09               = 0x00;
const uint8_t _TEMPHUM7_HEATER_CURRENT_9p17               = 0x01;
const uint8_t _TEMPHUM7_HEATER_CURRENT_15p24              = 0x02;
const uint8_t _TEMPHUM7_HEATER_CURRENT_21p31              = 0x03;
const uint8_t _TEMPHUM7_HEATER_CURRENT_27p39              = 0x04;
const uint8_t _TEMPHUM7_HEATER_CURRENT_33p46              = 0x05;
const uint8_t _TEMPHUM7_HEATER_CURRENT_39p53              = 0x06;
const uint8_t _TEMPHUM7_HEATER_CURRENT_45p61              = 0x07;
const uint8_t _TEMPHUM7_HEATER_CURRENT_51p68              = 0x08;
const uint8_t _TEMPHUM7_HEATER_CURRENT_57p76              = 0x09;
const uint8_t _TEMPHUM7_HEATER_CURRENT_63p83              = 0x0A;
const uint8_t _TEMPHUM7_HEATER_CURRENT_69p90              = 0x0B;
const uint8_t _TEMPHUM7_HEATER_CURRENT_75p98              = 0x0C;
const uint8_t _TEMPHUM7_HEATER_CURRENT_82p05              = 0x0D;
const uint8_t _TEMPHUM7_HEATER_CURRENT_88p13              = 0x0E;
const uint8_t _TEMPHUM7_HEATER_CURRENT_94p20              = 0x0F;


/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __TEMPHUM7_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* data registers */
const uint8_t _TEMPHUM7_MEASURE_RELATIVE_HUMIDITY_HOLD    = 0xE5;
const uint8_t _TEMPHUM7_MEASURE_RELATIVE_HUMIDITY_NOHOLD  = 0xF5;
const uint8_t _TEMPHUM7_MEASURE_TEMPERATURE_HOLD          = 0xE3;
const uint8_t _TEMPHUM7_MEASURE_TEMPERATURE_NOHOLD        = 0xF3;
const uint8_t _TEMPHUM7_READ_TEMPERATURE_FROM_PREVIOUS_RH = 0xE0;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __TEMPHUM7_DRV_SPI__

void temphum7_spiDriverInit(T_TEMPHUM7_P gpioObj, T_TEMPHUM7_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __TEMPHUM7_DRV_I2C__

void temphum7_i2cDriverInit(T_TEMPHUM7_P gpioObj, T_TEMPHUM7_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __TEMPHUM7_DRV_UART__

void temphum7_uartDriverInit(T_TEMPHUM7_P gpioObj, T_TEMPHUM7_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */


void temphum7_getData( uint8_t command_, uint8_t *dataOut_, uint8_t nData_ )
{
    hal_i2cStart( );
    hal_i2cWrite( _slaveAddress, &command_, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, dataOut_, nData_, END_MODE_STOP );
}

void temphum7_setData( uint8_t command_, uint8_t dataIn_ )
{
    uint8_t auxBuffer[2];
    
    auxBuffer[0] = command_;
    auxBuffer[1] = dataIn_;
    
    hal_i2cStart( );
    hal_i2cWrite( _slaveAddress, auxBuffer, 2, END_MODE_STOP );
}

float temphum7_getRelativeHumidity( uint8_t mode_ )
{
    uint16_t aux;
    float relativeHumidity_;
    uint8_t dataOut[2];
    
    if (mode_ == 0)
    {
        temphum7_getData( _TEMPHUM7_MEASURE_RELATIVE_HUMIDITY_HOLD, dataOut, 2 );
    }
    else if (mode_ == 1)
    {
        temphum7_getData( _TEMPHUM7_MEASURE_RELATIVE_HUMIDITY_NOHOLD, dataOut, 2 );
    }
    
    aux = dataOut[0];
    aux <<= 8;
    aux |= dataOut[1];
    
    relativeHumidity_  = (float)aux * 125;
    relativeHumidity_ /= 65536;
    relativeHumidity_ -= 6;
    
    return relativeHumidity_;
}

float temphum7_getTemperature ( uint8_t mode_ )
{
    uint16_t aux;
    float temperature_;
    uint8_t dataOut[2];

    if (mode_ == 0)
    {
        temphum7_getData( _TEMPHUM7_MEASURE_TEMPERATURE_HOLD, dataOut, 2 );
    }
    else if (mode_ == 1)
    {
        temphum7_getData( _TEMPHUM7_MEASURE_TEMPERATURE_NOHOLD, dataOut, 2 );
    }
    else if (mode_ == 2)
    {
        temphum7_getData( _TEMPHUM7_READ_TEMPERATURE_FROM_PREVIOUS_RH, dataOut, 2 );
    }

    aux = dataOut[0];
    aux <<= 8;
    aux |= dataOut[1];

    temperature_  = aux * 175.72;
    temperature_ /= 65536;
    temperature_ -= 46.85;

    return temperature_;
}

void temphum7_getElectronicSerialNumber( uint8_t *esnBuffer )
{
    uint8_t auxBuffer[2];

    auxBuffer[0] = 0xFA;
    auxBuffer[1] = 0x0F;
    
    hal_i2cStart( );
    hal_i2cWrite( _slaveAddress, auxBuffer, 2, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, &esnBuffer[0], 8, END_MODE_STOP );
    
    Delay_1ms( );
    
    auxBuffer[0] = 0xFC;
    auxBuffer[1] = 0xC9;
    
    hal_i2cStart( );
    hal_i2cWrite( _slaveAddress, auxBuffer, 2, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, &esnBuffer[8], 6, END_MODE_STOP );
}

uint8_t temphum7_getFirmwareRevision( void )
{
    uint8_t auxBuffer[2];
    uint8_t fwRevision_;

    auxBuffer[0] = 0x84;
    auxBuffer[1] = 0xB8;

    hal_i2cStart( );
    hal_i2cWrite( _slaveAddress, auxBuffer, 2, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, &fwRevision_, 1, END_MODE_STOP );
    
    return fwRevision_;
}

float temphum7_getHeaterCurrent( void )
{
    uint8_t auxBuffer[1];
    uint8_t auxByte;
    float heaterCurrent_;

    auxBuffer[0] = _TEMPHUM7_READ_HEATER_CONTROL_REGISTER;

    hal_i2cStart( );
    hal_i2cWrite( _slaveAddress, auxBuffer, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, &auxByte, 1, END_MODE_STOP );
    
    auxByte &= 0x0F;
    
    heaterCurrent_ = auxByte * 6.074;
    heaterCurrent_ += 3.09;

    return heaterCurrent_;
}

void temphum7_reset( void )
{
    uint8_t auxByte;
    
    auxByte = _TEMPHUM7_RESET;

    hal_i2cStart( );
    hal_i2cWrite( _slaveAddress, auxByte, 1, END_MODE_STOP );
}




/* -------------------------------------------------------------------------- */
/*
  __temphum7_driver.c

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