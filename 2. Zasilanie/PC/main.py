import sys
import numpy as np
import time

from sparkfunlib import CurrentSource
from rigollib import MiliAmperoMeter
from ina219lib import INA219
from pathlib import Path 

ina_current = []
rigol_current  = []

settings_lut = np.load("ina219_settings.npy",allow_pickle='TRUE').item()

try:
    f = open("chosen_settings.txt",'r')
    settings = f.readlines()
    
    current_source = CurrentSource()
    current_meter =  MiliAmperoMeter()
    ina = INA219()
    
    for setting in settings:
        setting = setting.strip().replace(",", "_")
        if Path(setting+".npy").is_file():
            print("File exsists")   
            sys.exit()
         
        #Calibration coefficient
        current_source.current_set(1000)
        I = current_meter.read_current()
        print(I)
        ina.callib(I)  
        #INA configuration
        ina_config = ina.callib_device(settings_lut[setting])
        print(ina_config)
        time.sleep(3)        
    
        #Acquisition          
        for i in range(1,101):
            print(i)
            current_source.current_set(i)
            I = ina.read_current()
            Iref = current_meter.read_current()
            ina_current.append(float(I))
            rigol_current.append(Iref)    
            print(float(I))
            print(Iref)  
        
        #Save data
        y =  np.array(ina_current)
        x =  np.array(rigol_current)
        data = np.array([x,y])
        np.save(setting+".npy",data)
        ina_current.clear()
        rigol_current.clear()
                 
    ina.exit()
    f.close()
        
except Exception as exc:
        print(exc)
               

        
    
    
        
    
    

                  
