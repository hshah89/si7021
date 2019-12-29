/*  These drivers are for the arduino IDE platform. 
    It also can be used with ESP8266 and ESP32.
    Really, any devices that can be connected using the I2C library
    that comes with the Arduino IDE

    This library for now only works with I2C wire interface. 
    
    Support for Two and Three wire SPI is coming at a later point.

    Author: Harit Shah

    References: SI7021 Datasheet
*/

#include "Arduino.h"
#include <Wire.h>

// Defines

#define NO_HOLD 0
#define HOLD 1

/* Commands */
#define meas_rel_humid_hold 0xE5
#define meas_rel_humid_no_hold 0xF5
#define meas_temp_hold 0xE3
#define meas_temp_no_hold 0xF3
#define meas_temp_from_rel_humid 0xE0
#define reset_chip 0xFE
#define write_user_reg_1 0xE6
#define write_user_reg_2 0xE7
#define write_heater_reg 0x51
#define read_heater_reg 0x11
#define read_id_byte1_reg_1 0xFA
#define read_id_byte1_reg_2 0x0F
#define read_id_byte2_reg_1 0xFC
#define read_id_byte2_reg_2 0xC9
#define read_fw_rev_reg_1 0x84
#define read_fw_rev_reg_2 0xB8

struct si7021_sensor_settings
{
public:
    uint8_t i2c_addr;
};

class SI7021
{
public:
    si7021_sensor_settings settings;

    SI7021(void);

    uint8_t begin(void);
    uint8_t begin_i2c(TwoWire &wirePort = Wire);

    uint8_t get_chip_id(void);
    uint8_t get_fw_rev(void);

    uint8_t read_reg(uint8_t offset);
    void write_reg(uint8_t offset, uint8_t write_data);

    float read_rel_humid(void);
    float read_temp(void);
    float read_temp_w_humid(void);

    void reset(void);
};