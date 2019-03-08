![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Temp_Hum_7 Click

---

- **CIC Prefix**  : TEMPHUM7
- **Author**      : Aleksandar Paunovic
- **Verison**     : 1.0.0
- **Date**        : Nov 2018.

---

### Software Support

We provide a library for the Temp_Hum_7 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2669/temp-hum-7-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

 Library contains functions for reading register content and setting register content
 Library contains functions for reading electronic serial number and firmware reviosion
 Library contains functions for reading temperature (C), humidity(%RH) and heater current (mA) values
 Library contains function  for device reset

Key functions :

- ``` void temphum7_setData( uint8_t command_, uint8_t dataIn_ ); ``` - sets one byte of register data
- ``` float temphum7_getRelativeHumidity( uint8_t mode_ ) ```         - performs relative humidity measurement and calculates relative humidity
- ``` float temphum7_getTemperature ( uint8_t mode_ ) ```             - performs temperature measurement and calculates temperature

**Examples Description**

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C and LOG
- Application Initialization - Initializes I2C driver, and sets 12-bit resolution for measurements
- Application Task - Calculates and Logs temperature and relative humidity


```.c

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

```


The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2669/temp-hum-7-click) page.

Other mikroE Libraries used in the example:

- I2C
- UART
- Conversions

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
