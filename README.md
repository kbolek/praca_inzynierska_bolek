##Current measurement

The description of the library functions:

>bool INA219_begin(TwoWire *theWire = &Wire);

The function prototype of the library's begin function. It is responsible for connecting the INA219 sensor witch microcontroller (Arduino) by I2C. 
It returns type boolean with a parameter of type TwoWire* that has a default value of &Wire.

The address of the device is assigned to macro INA219_ADDRESS and for INA219 is 0x40. 

>void setCalibration_16V_1A();

The function set up the parameters of the INA219 measurement like:

1. Bus voltage range values.
2. Value for gain bit.
3. Value for bus ADC resolution.
4. Value for shunt ADC resolution.
5. Value for shunt ADC resolution.




