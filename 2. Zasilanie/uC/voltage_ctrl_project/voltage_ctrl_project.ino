#include <Wire.h>
#include "INA219.h"

void setup(void) 
{
  Serial.begin(9600);
  INA219_begin();
}

void loop(void) 
{
    String serial = Serial.readStringUntil('\n');
    if(serial.substring(0,3) == "rvr"){
      Serial.print(String(read_voltage_reg(),10) + '\n');
    }
    else if(serial.substring(0,2) == "cc"){
      callib_current(serial.substring(3,6).toInt());
      Serial.print("Current callibrated");
    }
    else if(serial.substring(0,2) == "cv"){
      callib_voltage(serial.substring(3,6).toInt());
      Serial.print("Voltage callibrated");
    }
    else if(serial.substring(0,2) == "rc"){
      Serial.print(String(read_current(),10) + '\n');
    }
    else if(serial.substring(0,2) == "rv"){
      Serial.print(String(read_voltage(),10) + '\n');
    }
     
  }



