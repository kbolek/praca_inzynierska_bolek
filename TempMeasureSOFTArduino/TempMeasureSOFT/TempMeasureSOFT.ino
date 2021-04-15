#include <Adafruit_MAX31865.h>
#include <stdio.h>

#define SPI_CS 17
#define SPI_MOSI 16
#define SPI_MISO 14
#define SPI_CLK 15

#define RREF      430.0
#define RNOMINAL  100.0

Adafruit_MAX31865 thermo = Adafruit_MAX31865(SPI_CS, SPI_MOSI, SPI_MISO, SPI_CLK);

void setup() {
  Serial.begin(9600);
  thermo.begin(MAX31865_4WIRE);
}

void loop() {
  String ser = Serial.readStringUntil('\n');
  Serial.print(String(thermo.temperature(RNOMINAL, RREF)) + "\n");   
}
