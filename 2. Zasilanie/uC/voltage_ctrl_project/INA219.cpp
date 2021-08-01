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

void callib_voltage(int16_t measured_voltage_mv){
  /*ASSUMPTION: THE FUNCTION IS EXPRESSED AS Y=AX*/
  float coefficient = measured_voltage_mv/(read_voltage_reg()*0.01);
  EEPROM.put(0,coefficient);
}

float read_voltage(){
  float coefficient;
  EEPROM.get(0,coefficient);
  float voltage_mv = (read_voltage_reg()*0.01) * coefficient;
  return voltage_mv;
}

void callib_current(int16_t measured_current_ma){
  float calValue = (ADC_RESOLUTION * 0.00001)/(CURRENT_LSB*RSHUNT);
  float currentDivider_mA = 1.0/(CURRENT_LSB*1000.0);

  float coefficient = measured_current_ma/(((read_voltage_reg()*calValue)/ADC_RESOLUTION)/currentDivider_mA);
  EEPROM.put(1,coefficient);
}

float read_current(){
  float calValue = (ADC_RESOLUTION * 0.00001)/(CURRENT_LSB*RSHUNT);
  float currentDivider_mA = 1.0/(CURRENT_LSB*1000.0);

  float coefficient;
  EEPROM.get(1,coefficient);

  float current_ma = (((read_voltage_reg()*calValue)/ADC_RESOLUTION)/currentDivider_mA) * coefficient;

  return current_ma;

}



