/*************************************************** 
  This is a library for the Adafruit PT100/P1000 RTD Sensor w/MAX31865

  Designed specifically to work with the Adafruit RTD Sensor
  ----> https://www.adafruit.com/products/3328

  This sensor uses SPI to communicate, 4 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_MAX31865.h>
#include <stdio.h>
#include <string.h>

// Use software SPI: CS, DI, DO, CLK
#define SPI_CS 17
#define SPI_MOSI 16
#define SPI_MISO 14
#define SPI_CLK 15

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

Adafruit_MAX31865 thermo = Adafruit_MAX31865(SPI_CS, SPI_MOSI, SPI_MISO, SPI_CLK);

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit MAX31865 PT100 Sensor Test!");

  thermo.begin(MAX31865_4WIRE);  // set to 4WIRE
  char buffer[6];
  char start_flag;
}

void check_if_fault(){
  uint8_t fault = thermo.readFault();
  if (fault) {
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("TMP+HIGH+"); 
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("TMP+LOW+"); 
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("TMP+REFINM+"); 
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("TMP+RTDINM+"); 
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("TMP+VOL+"); 
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("TMP+UOVOL+"); 
    }
    thermo.clearFault();
  }
}

void loop() {
  uint16_t rtd = thermo.readRTD();
  char temp_message[7] ="+";
  char str_temp[6];
  char temperature_string[6];
  if(rtd>0){
      dtostrf(thermo.temperature(RNOMINAL, RREF),4,2,str_temp);
      sprintf(temperature_string,"%s",str_temp);
      strcat(temp_message,temperature_string);
      Serial.println(temp_message); 
  }

  //if(strcmp(buffer,"START\r") == 0 && start_flag == 1){
    //uint16_t rtd = thermo.readRTD();
    //uint8_t rtd_message
    //Serial.print("TMP+RTD+"); //Serial.println(rtd);
    //float ratio = rtd;
    //ratio /= (1<<15); //MAX31865 has a 15-bit ADC which uses the voltage across the reference resistor as its reference voltage
    //Serial.print("Ratio = "); Serial.println(ratio,8); //this will be calculated by the computer
    //Serial.print("Resistance = "); Serial.println(RREF*ratio,8); //this will be calculated by the computer 
    //Serial.print("Temperature = \n"); //Serial.println(thermo.temperature(RNOMINAL, RREF));
    // Check and print any faults
  //}
  delay(1000);
}
