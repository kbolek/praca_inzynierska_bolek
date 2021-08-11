#include <Wire.h>
#include <EEPROM.h>
#include "Arduino.h"
#include "INA219.h"

Adafruit_I2CDevice *i2c_dev = new Adafruit_I2CDevice(INA219_ADDRESS, &Wire);;

Adafruit_BusIO_Register shunt_voltage_reg =
    Adafruit_BusIO_Register(i2c_dev, INA219_REG_SHUNTVOLTAGE, 2, MSBFIRST);

Adafruit_BusIO_Register bus_voltage_reg =
    Adafruit_BusIO_Register(i2c_dev, INA219_REG_BUSVOLTAGE, 2, MSBFIRST);

Adafruit_BusIO_Register config_reg =
            Adafruit_BusIO_Register(i2c_dev, INA219_REG_CONFIG, 2, MSBFIRST);

uint16_t config;

/*=========================================================================
                    INA219 CONFIGURATION FUNCTIONS
**************************************************************************/
void INA219_configure(){
    config = INA219_CONFIG_BVOLTAGERANGE_16V |
                      INA219_CONFIG_GAIN_4_160MV | INA219_CONFIG_BADCRES_12BIT_128S_69MS| 
                      INA219_CONFIG_SADCRES_12BIT_128S_69MS| 
                      INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS; 

    i2c_dev->begin();                  
    config_reg.write(config, 2);
}


/*=========================================================================
            FUNCTIONS FOR READING REGISTERS
**************************************************************************/
int16_t register_shunt(){
  uint16_t reg_value;
  
  config_reg.write(config,2);
  shunt_voltage_reg.read(&reg_value);

  return reg_value;
}

int16_t register_bus(){
  uint16_t reg_value;

  config_reg.write(config,2);
  bus_voltage_reg.read(&reg_value);

  return (reg_value>>3);
}


/*=========================================================================
            FUNCTIONS FOR CURRENT
**************************************************************************/

void current_callib(float measured_mA){
  float coefficient = measured_mA/register_shunt();
  EEPROM.put(EEPROM_CUR_COEF_ADDR,coefficient);
}

float current_read_coefficient(){
  float coefficient;
  EEPROM.get(EEPROM_CUR_COEF_ADDR,coefficient);
  return coefficient;
}

float current_read(){
  float coefficient;
  EEPROM.get(0,coefficient);
  return register_shunt() * coefficient;
}

/*=========================================================================
            FUNCTIONS FOR VOLTAGE
**************************************************************************/
void voltage_callib(float measured_mV){
  float coefficient = measured_mV/register_bus();
  EEPROM.put(EEPROM_VOL_COEF_ADDR,coefficient);
}

float voltage_read_coefficient(){
  float coefficient;
  EEPROM.get(EEPROM_VOL_COEF_ADDR,coefficient);
  return coefficient;
}

float voltage_read(){
  float coefficient;
  EEPROM.get(EEPROM_VOL_COEF_ADDR,coefficient);
  return register_bus() * coefficient;
}