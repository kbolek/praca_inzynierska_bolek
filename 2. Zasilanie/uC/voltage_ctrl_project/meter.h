#include <Wire.h>
#include <EEPROM.h>
#include "Arduino.h"
#include "INA219.h"
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>


#define DEFAULT_CONFIG (INA219_CONFIG_BVOLTAGERANGE_16V | \
               INA219_CONFIG_GAIN_1_40MV | \
               INA219_CONFIG_BADCRES_12BIT_128S_69MS | \
               INA219_CONFIG_SADCRES_12BIT_128S_69MS | \
               INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS)

class Meter {  
   private:   
      Adafruit_BusIO_Register *config_reg;
      Adafruit_BusIO_Register *voltage_reg;
      int eeprom_ix;     
      int shif_nr;      
      float callib_coeff;       
   public:
      static Adafruit_I2CDevice *i2c_dev;
      static unsigned char eeprom_ptr;
      uint16_t device_configuration;

      Meter(int voltage_type, int  _shif_nr){ 
         if (!Meter::i2c_dev) {
            Meter::i2c_dev = new Adafruit_I2CDevice(INA219_ADDRESS, &Wire);
         }
      
         config_reg  = new Adafruit_BusIO_Register(i2c_dev, INA219_REG_CONFIG, 2, MSBFIRST);
         voltage_reg = new Adafruit_BusIO_Register(i2c_dev, voltage_type, 2, MSBFIRST);      

         device_configuration = DEFAULT_CONFIG;
         
         eeprom_ix = eeprom_ptr;
         eeprom_ptr += sizeof(float);

         EEPROM.get(eeprom_ptr,callib_coeff);         
         
         shif_nr = _shif_nr;
      } 
      
      uint16_t register_read(){
         uint16_t reg_value;         
         config_reg->write(device_configuration, 2);
         voltage_reg->read(&reg_value);         
         return (reg_value >> shif_nr);
      }
      
      void callib(float measured_mili){
        callib_coeff = measured_mili/register_read();
        EEPROM.put(eeprom_ix,callib_coeff);
      }

      float read_coefficient(){
         return callib_coeff;
      }

      float read(){
        return (register_read() * callib_coeff);
      }     
};
