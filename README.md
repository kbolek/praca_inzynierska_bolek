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

>int16_t read_voltage_reg();

The function simply read the value of the shunt voltage register by I2C. 

>void callib_voltage(int16_t measured_voltage_mv);

The function is wrote to determine the voltage coefficient by division of actuall measured voltage (by accurate multimetr) and voltage appointed by the value of the shunt voltage register (multiply by 0.01 because of the constant Shunt Volatge LSB of 10µV).


