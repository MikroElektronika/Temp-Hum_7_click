/*
Example for Temp_Hum_7 Click

    Date          : Nov 2018.
    Author        : Aleksandar Paunovic

Test configuration FT90x :
    
    MCU                : FT900
    Dev. Board         : EasyFT90x v7 
    FT90x Compiler ver : v2.3.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C and LOG
- Application Initialization - Initializes I2C driver, and sets 12-bit resolution for measurements
- Application Task - Calculates and Logs temperature and relative humidity
*/

#include "Click_Temp_Hum_7_types.h"
#include "Click_Temp_Hum_7_config.h"

char text[50];
float temperature;
float relativeHumidity;


void systemInit( )
{
    mikrobus_i2cInit( _MIKROBUS1, &_TEMPHUM7_I2C_CFG[0] );
    Delay_ms(500);
    mikrobus_logInit( _LOG_USBUART, 9600 );
    Delay_ms(100);
    
    mikrobus_logWrite( " > > > sys init done < < < ", _LOG_LINE );
}

void applicationInit( )
{
    temphum7_i2cDriverInit( (T_TEMPHUM7_P)&_MIKROBUS1_GPIO, (T_TEMPHUM7_P)&_MIKROBUS1_I2C, _TEMPHUM7_DEVICE_ADDRESS );
    temphum7_setData( _TEMPHUM7_WRITE_RHT_USER_REGISTER_1, _TEMPHUM7_RESOLUTION_12_BIT );
    
    mikrobus_logWrite( " > > > app init done < < < ", _LOG_LINE );
}

void applicationTask( )
{
    mikrobus_logWrite( " ", _LOG_LINE );
    
    temperature = temphum7_getTemperature( _TEMPHUM7_HOLD_MASTER_MODE );
    FloatToStr( temperature, text );
    mikrobus_logWrite( " > > > temperature        : ", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_TEXT );
    mikrobus_logWrite( " C", _LOG_LINE );

    relativeHumidity = temphum7_getRelativeHumidity( _TEMPHUM7_HOLD_MASTER_MODE );
    FloatToStr( relativeHumidity, text );
    mikrobus_logWrite( " > > > relative humidity  : ", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_TEXT );
    mikrobus_logWrite( " %RH", _LOG_LINE );

    Delay_ms(1000);
}

void main( )
{
    systemInit( );
    applicationInit( );

    while (1)
    {
        applicationTask( );
    }
}