#ifndef INA219_H
#define INA219_H

#include "Arduino.h"
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>


/*=========================================================================
    LIBRARY MACROS FOR DESIRE PARAMETERS OF THE MEASUREMENT
**************************************************************************/

/** DEFAULT I2C ADDRESS **/
#define INA219_ADDRESS (0x40)
#define INA219_READ (0x01)

/*CONFIG REGISTER (R/W)*/
#define INA219_REG_CONFIG (0x00)
#define INA219_CONFIG_RESET (0x8000)
#define INA219_CONFIG_BVOLTAGERANGE_MASK (0x2000)

/** MASK FOR GAIN BITS**/
#define INA219_CONFIG_GAIN_MASK (0x1800)

#define INA219_CONFIG_GAIN_1_40MV (0x0000)
#define INA219_CONFIG_GAIN_2_80MV (0x0800) 
#define INA219_CONFIG_GAIN_4_160MV (0x1000)
#define INA219_CONFIG_GAIN_8_320MV (0x1800)

/** MASK FOR BUS ADC RESOLUTION BITS**/
#define INA219_CONFIG_BADCRES_MASK (0x0780)
#define INA219_CONFIG_BADCRES_12BIT_128S_69MS (0x0780)

/** MASK FOR SHUNT ADC RESOLUTION BITS **/
#define INA219_CONFIG_SADCRES_MASK (0x0078)
#define INA219_CONFIG_SADCRES_12BIT_128S_69MS (0x0078)

/** OPERATING BITS MODE **/
#define INA219_CONFIG_MODE_MASK (0x0007)
#define INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS (0x07)

/** BUS VOLTAGE RANGE VALUE **/
#define INA219_CONFIG_BVOLTAGERANGE_16V (0x0000)

/** SHUNT VOLTAGE REGISTER **/
#define INA219_REG_SHUNTVOLTAGE (0x01)

/** BUS VOLTAGE REGISTER**/
#define INA219_REG_BUSVOLTAGE (0x02)

/**EEPROM ADDRESS FOR CURRENT COEFFICIENT **/
#define EEPROM_CUR_COEF_ADDR 0

/**EEPROM ADDRESS FOR VOLTAGE COEFFICIENT **/
#define EEPROM_VOL_COEF_ADDR 4

/*=========================================================================
                         LIBRARY FUNCTIONS
**************************************************************************/
void INA219_configure();
bool success();

int16_t register_shunt();
int16_t register_bus();

void current_callib(float measured_mA);
float current_read();
float current_read_coefficient();

void voltage_callib(float measured_mV);
float voltage_read();
float voltage_read_coefficient();

extern Adafruit_BusIO_Register shunt_voltage_reg;
extern Adafruit_BusIO_Register bus_voltage_reg;
extern Adafruit_BusIO_Register config_reg;
extern uint16_t config;

#endif
