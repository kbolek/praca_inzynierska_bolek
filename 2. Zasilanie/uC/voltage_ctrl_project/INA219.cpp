#include <Wire.h>
#include <EEPROM.h>
#include "Arduino.h"
#include "INA219.h"

Adafruit_I2CDevice *i2c_dev = NULL;
uint8_t ina219_i2caddr = -1;
bool _success;
uint8_t callib_vol_addr;

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

  Adafruit_BusIO_Register calibration_reg =
      Adafruit_BusIO_Register(i2c_dev, INA219_REG_CALIBRATION, 2, MSBFIRST);
  calibration_reg.write(INA219_CAL_VALUE, 2);

    uint16_t config = INA219_CONFIG_BVOLTAGERANGE_16V |
                      INA219_CONFIG_GAIN_1_40MV  | INA219_CONFIG_BADCRES_12BIT_128S_69MS| 
                      INA219_CONFIG_SADCRES_12BIT_128S_69MS| 
                      INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS; 
    Adafruit_BusIO_Register config_reg =
            Adafruit_BusIO_Register(i2c_dev, INA219_REG_CONFIG, 2, MSBFIRST);
    _success = config_reg.write(config, 2);

}

int16_t read_voltage_reg() {
  uint16_t value;
  Adafruit_BusIO_Register shunt_voltage_reg =
      Adafruit_BusIO_Register(i2c_dev, INA219_REG_SHUNTVOLTAGE, 2, MSBFIRST);
  _success = shunt_voltage_reg.read(&value);
  return value;
}

int16_t read_current_reg(){
  uint16_t value;

  /*sometimes a sharp load will reset the INA219, which will reset cal register*/
  Adafruit_BusIO_Register calibration_reg =
      Adafruit_BusIO_Register(i2c_dev, INA219_REG_CALIBRATION, 2, MSBFIRST);
  calibration_reg.write(INA219_CAL_VALUE, 2);

  Adafruit_BusIO_Register current_reg =
      Adafruit_BusIO_Register(i2c_dev, INA219_REG_CURRENT, 2, MSBFIRST);
  _success = current_reg.read(&value);
  return value;
}

void callib_voltage(float measured_voltage_mv){
  /*ASSUMPTION: THE FUNCTION IS EXPRESSED AS Y=AX*/
  float coefficient = measured_voltage_mv/(read_voltage_reg());
  EEPROM.put(0,coefficient);
}

float read_voltage(){
  float coefficient;
  EEPROM.get(0,coefficient);
  float voltage_mv = (read_voltage_reg()) * coefficient;
  return voltage_mv;
}

void callib_current(float measured_current_ma){

  float coefficient = measured_current_ma/read_current_reg();
  EEPROM.put(1,coefficient);

}

float read_current(){
 
  float coefficient;
  EEPROM.get(1,coefficient);
  float current_ma = (read_current_reg()) * coefficient;
  return current_ma;
}



