#include <Wire.h>
#include "INA219.h"
#include "command_decoder.h"

void setup(void) 
{
  Serial.begin(9600);
  INA219_begin();
}

void loop(void) 
{
  char serial_arr[MAX_STRING_LTH];
  uint16_t voltage_value;
  uint16_t bus_voltage_value;
  String serial = Serial.readStringUntil('\n');
  serial.toCharArray(serial_arr, MAX_STRING_LTH);

  decode_msg(serial_arr);

  if(token_nr > 0 && as_token[0].as_type == KEYWORD){
    switch(as_token[0].value.as_keyword){
      case RVR:
      shunt_voltage_reg.read(&voltage_value);
      Serial.print(String(voltage_value,10) + '\n');
      break;
      case RBR:
       bus_voltage_reg.read(&bus_voltage_value);
       // Shift to the right 3 to drop CNVR and OVF and multiply by LSB
       bus_voltage_value = (int16_t)((bus_voltage_value >> 3) * 4);
       Serial.print(String(bus_voltage_value,10) + '\n');
      break;
      case CC:
        if(as_token[1].as_type == NUMBER){
          callib_current(int(as_token[1].value.number));
          Serial.print("current_calibrated\n");
        }
        else{
          Serial.print("unknowncommand\n");
        }
      break;
      case CV:
        if(as_token[1].as_type == NUMBER){
          callib_voltage(int(as_token[1].value.number));
          Serial.print("voltage_calibrated\n");
        }
        else{
          Serial.print("unknowncommand\n");
        }
      break;
      case RC:
        Serial.print(String(read_current(),10) + '\n'); 
      break;
      case RV:
        Serial.print(String(read_voltage(),10) + '\n');
      break;
      case RCC:
        Serial.print(String(read_current_coefficient(),10) + '\n');
      break;
      case RVC:
        Serial.print(String(read_voltage_coefficient(),10) + '\n');
      break;
    }
  }
}