// I N C L U D E S
//-------------------------------------------------------------------------------------------------
#include <Wire.h>
#include "si7021.h"

// D E F I N E S
//-------------------------------------------------------------------------------------------------
#define BAUD_RATE 115200

// G L O B A L  V A R I A B L E S
//-------------------------------------------------------------------------------------------------
float temperature; // Storing measured temperature reading
float humidity;    // Storing measured humidity reading

uint8_t chip_id; // Storing SI7021 Chip ID

SI7021 sensor_si7021;

// S E T U P
//-------------------------------------------------------------------------------------------------
void setup()
{

    Wire.begin();
    Serial.begin(BAUD_RATE);

    Serial.println("SI-7021 - Temperature and Humidity Sensor\n");
    chip_id = sensor_si7021.begin();
    if (chip_id)
    {
        Serial.println("Deviced Detected:\tSi7021");
    }
    Serial.print("Firmware Version:\t");
    if (sensor_si7021.get_fw_rev() == 0xFF)
    {
        Serial.print("1.0");
    }
    else if (sensor_si7021.get_fw_rev() == 0x20)
    {
        Serial.print("2.0");
    }

    Serial.println("\n\nTemp\t\tHumidity");
    Serial.println("----------------------------------------------\r");
    getData();
}

// L O O P
//-------------------------------------------------------------------------------------------------
void loop()
{
    delay(10e3);
    getData();
}

// F U N C T I O N S
//-------------------------------------------------------------------------------------------------
void getData()
{
    humidity = sensor_si7021.read_rel_humid();
    temperature = sensor_si7021.read_temp();
    Serial.print(temperature);
    Serial.print(" ºF \t");
    Serial.print(humidity);
    Serial.print(" % \t");
    Serial.print("\n");
}