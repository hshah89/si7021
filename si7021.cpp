/*  These drivers are for the arduino IDE platform. 
    It also can be used with ESP8266 and ESP32.
    Really, any devices that can be connected using the I2C library
    that comes with the Arduino IDE

    This library for now only works with I2C wire interface. 
    
    Support for Two and Three wire SPI is coming at a later point.

    Author: Harit Shah

    References: SI7021 Datasheet
*/

#include "si7021.h"

/* Settings, Configuration */

SI7021::SI7021(void)
{
    settings.i2c_addr = 0x40;
}

/* Begin and Initialize I2C */
uint8_t SI7021::begin()
{
    uint8_t chip_id;

    Wire.begin();

    chip_id = get_chip_id();
    if (chip_id == 0x15)
    {
        return 1;
    }
    else
        return 0;
}

uint8_t SI7021::get_chip_id()
{
    uint8_t serial_number_1[8];
    uint8_t serial_number_2[6];

    Wire.beginTransmission(settings.i2c_addr);
    Wire.write(read_id_byte1_reg_1);
    Wire.write(read_id_byte1_reg_2);
    Wire.endTransmission();

    Wire.requestFrom(settings.i2c_addr, 8);
    for (int x = 0; x < 8; x++)
    {
        serial_number_1[x] = Wire.read();
    }

    Wire.beginTransmission(settings.i2c_addr);
    Wire.write(read_id_byte2_reg_1);
    Wire.write(read_id_byte2_reg_2);
    Wire.endTransmission();

    Wire.requestFrom(settings.i2c_addr, 6);
    for (int x = 0; x < 6; x++)
    {
        serial_number_2[x] = Wire.read();
    }

    return serial_number_2[0];
}

uint8_t SI7021::get_fw_rev()
{
    uint8_t firmware_rev;

    Wire.beginTransmission(settings.i2c_addr);
    Wire.write(read_fw_rev_reg_1);
    Wire.write(read_fw_rev_reg_2);
    Wire.endTransmission();

    Wire.requestFrom(settings.i2c_addr, 1);

    firmware_rev = Wire.read();

    return firmware_rev;
}

float SI7021::read_rel_humid()
{

    uint8_t humid_msb;
    uint8_t humid_lsb;
    uint16_t humid;
    float f_humid;

    Wire.beginTransmission(settings.i2c_addr);
    Wire.write(meas_rel_humid_hold);
    Wire.endTransmission();

    Wire.requestFrom(settings.i2c_addr, 2);
    humid_msb = Wire.read();
    humid_lsb = Wire.read();

    humid = (humid_msb << 8) | humid_lsb;

    f_humid = ((125.0 * humid) / 65536) - 6.0;

    return f_humid;
}

float SI7021::read_temp()
{
    uint8_t temp_msb;
    uint8_t temp_lsb;
    uint16_t temp;
    float f_temp;

    Wire.beginTransmission(settings.i2c_addr);
    Wire.write(meas_temp_hold);
    Wire.endTransmission();

    Wire.requestFrom(settings.i2c_addr, 2);
    temp_msb = Wire.read();
    temp_lsb = Wire.read();

    temp = (temp_msb << 8) | temp_lsb;

    f_temp = ((175.72 * temp) / 65536) - 46.85;

    f_temp = (f_temp * 1.8) + 32.0;

    return f_temp;
}

float SI7021::read_temp_w_humid()
{
}