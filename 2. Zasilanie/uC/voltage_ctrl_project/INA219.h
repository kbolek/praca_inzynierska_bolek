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

/*RSHUNT*/
#define INA219_RSHUNT 0.1f
#define INA219_ADC_RESOLUTION 4096.0f
#define INA219_CURRENT_LSB 0.000031f

#define INA219_CAL_VALUE ((INA219_ADC_RESOLUTION * 0.00001f) / (INA219_CURRENT_LSB*INA219_RSHUNT))
#define INA219_CURRENT_DIVIDER (1.0f / (INA219_CURRENT_LSB * 1000.0f) )

/*=========================================================================
                         LIBRARY FUNCTIONS
**************************************************************************/

bool INA219_begin(TwoWire *theWire = &Wire);
void setCalibration_16V_1A();
bool success();

void callib_voltage(float measured_voltage_mv);
float read_voltage();
float read_voltage_coefficient();

void callib_current(float measured_current_ma);
float read_current();
float read_current_coefficient();

extern Adafruit_BusIO_Register shunt_voltage_reg;
extern Adafruit_BusIO_Register bus_voltage_reg;

#endif
