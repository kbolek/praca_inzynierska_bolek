from current_load import CurrentSource
from rigol_mesure import MiliAmperoMeter
from ina_measurement import INA219
from pathlib import Path 
import sys
import numpy as np
from matplotlib import pyplot as plt

NAME = "SWEEP CURRENT 1-100mA (DC)"

ina_current = []
rigol_current  = []

if Path(NAME+".npy").is_file():
    print("File exsists")   
    sys.exit()
else:
    try:
        current_source = CurrentSource()
        current_meter =  MiliAmperoMeter()
        ina = INA219()
    
        #Calibration
        current_source.current_set(1000)
        I = float(current_meter.read_current()[1:])*1000
        print(I)
        ina.callib(I)          
    
        #Acquisition          
        for i in range(1,100):
            print(i)
            current_source.current_set(i)
            I = ina.read_current()
            Iref = float(current_meter.read_current()[1:])*1000
            ina_current.append(float(I))
            rigol_current.append(Iref)      
            print(float(I))
            print(Iref)
    
        ina.exit()
               
    except Exception as exc:
        print(exc)

    finally:
        
        y =  np.array(ina_current)
        x = np.array(rigol_current)
         
        y_std = np.std(y)
        y_mean = np.mean(y)
         
        plt.figure(figsize=(12.8, 9.6))
       
        plt.title("Current measurement (std: {:.3f}, mean: {:.2f}) for ".format(y_std, y_mean) + NAME ,fontsize=17)
        plt.ylabel("Current measured by INA219 (mA)")
        plt.xlabel("Current measured by Rigol (mA)")
          
         
        plt.scatter(x,y)
        plt.show() 
         
        data = np.array([x,y])
        np.save(NAME+".npy",data)    
    
    

                  
