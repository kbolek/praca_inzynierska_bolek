import sys
from pathlib import Path
import numpy as np 
f = open("chosen_settings.txt",'r')

settings = f.readlines()
settings_lut = np.load("ina219_settings.npy",allow_pickle='TRUE').item()
    
for setting in settings:
        setting = setting.strip().replace(",", "_")
        if Path(setting+".npy").is_file():
            print("File exsists")   
            sys.exit()    
        print(settings_lut[setting])
    