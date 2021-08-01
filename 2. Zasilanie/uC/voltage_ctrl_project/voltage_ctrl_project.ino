#include <Wire.h>
#include "INA219.h"

void setup(void) 
{
  Serial.begin(9600);
  INA219_begin();
  callib_voltage(10);
  callib_current(100);
}

void loop(void) 
{
  String serial = Serial.readStringUntil('\n');
  Serial.print(String(read_current(),10) + '\n');
}
