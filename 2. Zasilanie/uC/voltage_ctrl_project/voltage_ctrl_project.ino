#include <Wire.h>
#include "meter.h"
#include "command_decoder.h"

Adafruit_I2CDevice *Meter::i2c_dev = NULL;
unsigned char Meter::eeprom_ptr = 0;
Meter current(INA219_REG_SHUNTVOLTAGE,0);
Meter voltage(INA219_REG_BUSVOLTAGE,3); 

void setup(void) 
{
  pinMode(13,OUTPUT);
  Serial.setTimeout(-1);
  Serial.begin(9600);
  
  
  Meter::i2c_dev->begin();
}


void loop(void) 
{
  digitalWrite(13,HIGH);
  char serial_arr[MAX_STRING_LTH];
  String serial = Serial.readStringUntil('\r');
  serial.toCharArray(serial_arr, MAX_STRING_LTH);
  
  decode_msg(serial_arr);

  if((token_nr > 0) && (as_token[0].as_type == KEYWORD)){
    switch(as_token[0].value.as_keyword){
      case RS:     
      Serial.print(String(current.register_read(),10) + '\n');
      break;
      case RB:
       Serial.print(String(voltage.register_read(),10) + '\n');
      break;
      case CC:
        if(as_token[1].as_type == NUMBER){
          current.callib(int(as_token[1].value.number));
          Serial.print("current_calibrated\n");
        }
        else{
          Serial.print("unknowncommand\n");
        }
      break;
      case CR:
        Serial.print(String(current.read(),10) + '\n'); 
      break;
      case CRC:
        Serial.print(String(current.read_coefficient(),10) + '\n');
      break;

      case VC:
        if(as_token[1].as_type == NUMBER){
          voltage.callib(int(as_token[1].value.number));
          Serial.print("voltage_calibrated\n");
        }
        else{
          Serial.print("unknowncommand\n");
        }
      break;
      case VR:
        Serial.print(String(voltage.read(),10) + '\n'); 
      break;
      case VRC:
        Serial.print(String(voltage.read_coefficient(),10) + '\n');
      break;
    }
  }
  else{
    Serial.print("unknowncommand\n");
  }
}
