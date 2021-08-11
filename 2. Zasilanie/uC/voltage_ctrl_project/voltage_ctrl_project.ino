#include <Wire.h>
#include "INA219.h"
#include "command_decoder.h"

void setup(void) 
{
  Serial.setTimeout(-1);
  Serial.begin(9600);
  INA219_configure();
}

void loop(void) 
{
  char serial_arr[MAX_STRING_LTH];
  String serial = Serial.readStringUntil('\r');
  serial.toCharArray(serial_arr, MAX_STRING_LTH);

  decode_msg(serial_arr);

  if((token_nr > 0) && (as_token[0].as_type == KEYWORD)){
    switch(as_token[0].value.as_keyword){
      case RS:     
      Serial.print(String(register_shunt(),10) + '\n');
      break;
      case RB:
       Serial.print(String(register_bus(),10) + '\n');
      break;
      case CC:
        if(as_token[1].as_type == NUMBER){
          current_callib(int(as_token[1].value.number));
          Serial.print("current_calibrated\n");
        }
        else{
          Serial.print("unknowncommand\n");
        }
      break;
      case CR:
        Serial.print(String(current_read(),10) + '\n'); 
      break;
      case CRC:
        Serial.print(String(current_read_coefficient(),10) + '\n');
      break;

      case VC:
        if(as_token[1].as_type == NUMBER){
          voltage_callib(int(as_token[1].value.number));
          Serial.print("voltage_calibrated\n");
        }
        else{
          Serial.print("unknowncommand\n");
        }
      break;
      case VR:
        Serial.print(String(voltage_read(),10) + '\n'); 
      break;
      case VRC:
        Serial.print(String(voltage_read_coefficient(),10) + '\n');
      break;
    }
  }
  else{
    Serial.print("unknowncommand\n");
  }
}