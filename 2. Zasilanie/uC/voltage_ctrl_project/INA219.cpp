#include <Wire.h>
#include <EEPROM.h>
#include "Arduino.h"
#include "INA219.h"

Adafruit_I2CDevice *i2c_dev = NULL;
uint8_t ina219_i2caddr = -1;
bool _success;

/*=========================================================================
                    INA219 CONFIGURATION FUNCTIONS
**************************************************************************/

bool INA219_begin(TwoWire *theWire){
    ina219_i2caddr = INA219_ADDRESS;

    if (!i2c_dev) {
        i2c_dev = new Adafruit_I2CDevice(ina219_i2caddr, theWire);
    }

    if (!i2c_dev->begin()) {
        return false;
    }

    if(_success != true){
        return false;
    }

    return true;
}

void setCalibration_16V_1A(){
    uint16_t config = INA219_CONFIG_BVOLTAGERANGE_16V |
                      INA219_CONFIG_GAIN_1_40MV  | INA219_CONFIG_BADCRES_12BIT_128S_69MS| 
                      INA219_CONFIG_SADCRES_12BIT_128S_69MS| 
                      INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS; 

    Adafruit_BusIO_Register config_reg =
            Adafruit_BusIO_Register(i2c_dev, INA219_REG_CONFIG, 2, MSBFIRST);
    _success = config_reg.write(config, 2);

    shunt_voltage_reg =
    Adafruit_BusIO_Register(i2c_dev, INA219_REG_SHUNTVOLTAGE, 2, MSBFIRST);
}

/*=========================================================================
        INA219 FUNCTIONS FOR READING THE CURRENT
**************************************************************************/
void callib_current(float measured_current_ma){
  /*float coefficient = measured_current_ma/read_current_reg();*/
  /*TODO:: callib current by taking the values from shunt voltage register and bus voltage register */
  float coefficient = 1.0f;
  EEPROM.put(1,coefficient);
}

float read_current(){
  float coefficient;
  EEPROM.get(1,coefficient);
  //return read_current_reg() * coefficient;
  return 20 * coefficient;
}

float read_current_coefficient(){
  float coefficient;
  EEPROM.get(1,coefficient);
  return coefficient;
}

/*=========================================================================
        INA219 FUNCTIONS FOR READING THE SHUNT VOLTAGE
**************************************************************************/
void callib_voltage(float measured_voltage_mv){
  /*ASSUMPTION: THE FUNCTION IS EXPRESSED AS Y=AX*/
  uint16_t voltage_value;

  shunt_voltage_reg.read(&voltage_value);
  float coefficient = measured_voltage_mv/voltage_value;
  EEPROM.put(0,coefficient);
}

float read_voltage(){
  float coefficient;
  uint16_t voltage_value;
  
  shunt_voltage_reg.read(&voltage_value);
  EEPROM.get(0,coefficient);
  return voltage_value * coefficient;
}

float read_voltage_coefficient(){
  float coefficient;
  EEPROM.get(0,coefficient);
  return coefficient;
}


