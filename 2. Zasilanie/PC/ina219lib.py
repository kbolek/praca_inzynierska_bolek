import time
import numpy as np
from serialhandler import SerialHandler

settings_lut = np.load("ina219_settings.npy",allow_pickle='TRUE').item()

corner_settings = ['40MV_1S_9BIT','40MV_1S_12BIT','40MV_128S_12BIT','320MV_1S_9BIT', '320MV_1S_12BIT', '320MV_128S_12BIT']

class INA219(SerialHandler):          
    def __init__(self):
        super().connect("COM6")
        time.sleep(2)
        
    def read_current(self):
       return super().serial_wr('cr\r')
   
    def callib_device(self,value):
        return super().serial_wr("cd " + str(value) + "\r")
    
    def callib(self,value):
       return super().serial_wr("cc " + str(value) + "\r")
   
    def debug(self):
        return super().serial_wr('dbg\r')
        
              
if __name__ == '__main__':
    ina = INA219()
    
    ina.callib(100)
    time.sleep(0.5)
    for setting in corner_settings:
            print(settings_lut[setting])
            print(ina.callib_device(settings_lut[setting]))
            print(ina.read_current())         
    ina.exit()

    