import sys
import numpy as np
import time

from matplotlib import pyplot as plt
from sparkfunlib import CurrentSource
from rigollib import MiliAmperoMeter
from ina219lib import INA219
from pathlib import Path 

NAME = "CORNER_SETTINGS2"
MEASURE_RANGE = 100

settings_lut = np.load("ina219_settings.npy",allow_pickle='TRUE').item()
settings = ['40MV_1S_9BIT','40MV_1S_12BIT','40MV_128S_12BIT','320MV_1S_9BIT', '320MV_1S_12BIT', '320MV_128S_12BIT']

ina_current = np.zeros(shape=(len(settings),MEASURE_RANGE))
rigol_current  = []

if Path(NAME+".npy").is_file():
    print("File exsists")   
    sys.exit()

try:
    current_source = CurrentSource()
    current_meter =  MiliAmperoMeter()
    ina = INA219()
    
    #Calibration
    current_source.current_set(1000)
    I = current_meter.read_current()
    print(I)
    ina.callib(I)  
    time.sleep(2)        
    
    #Acquisition          
    for i in range(1,MEASURE_RANGE+1):
        print(i)
        current_source.current_set(i)
        
        for count,ina_setting in enumerate(settings):
            ina.callib_device(settings_lut[ina_setting])
            time.sleep(1)
            ina_current[count][i-1] = float(ina.read_current())
            print(ina_current[count][i-1]) 
            time.sleep(1)         
        Iref = current_meter.read_current()
        rigol_current.append(Iref)      
            
    ina.exit()
        
except Exception as exc:
        print(exc)
                
finally:        
        x = np.array(rigol_current)
        configs = np.array(settings)
        
        for count,config in enumerate(settings):
            y = ina_current[count]
            y_std = np.std(y)
            y_mean = np.mean(y)
            
            plt.figure(figsize=(12.8, 9.6))
        
            plt.title("Current measurement (std: {:.3f}, mean: {:.2f}) for ".format(y_std, y_mean) + config ,fontsize=17)
            plt.ylabel("Current measured by INA219 (mA)")
            plt.xlabel("Current measured by Rigol (mA)")
          
            plt.scatter(x,y)
            plt.show()                  
        
        data_x = np.array(x)
        data_y = ina_current
        np.savez(NAME+".npz",x = data_x,y = data_y,title = configs)
    
    
        
    
    

