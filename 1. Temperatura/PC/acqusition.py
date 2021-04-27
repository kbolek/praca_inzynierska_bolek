import serial
import keyboard
import sys 
import numpy as np
from matplotlib import pyplot as plt
import pause
from pathlib import Path 
import time

PORT_NAME = "COM5" 
BAUDRATE  = 9600 
TIMEOUT   = 0.5
PERIOD    = 0.5 

FILE_PATH = "acquisition.npy"  

temperature_l = []
time_l = []

if Path(FILE_PATH).is_file():
    print("File exsists")   
    sys.exit()
        
try:
        
    with serial.Serial(PORT_NAME,BAUDRATE,timeout = TIMEOUT) as ser:
            start_time = time.time()
            while(not keyboard.is_pressed(' ')):
                ser.write('s\n'.encode())
                rx_data =  ser.readline().decode('utf-8').rstrip()
                print(rx_data)
                temperature_l.append(float(rx_data))   
                time_l.append(time.time() - start_time)
                pause.seconds(PERIOD)
except Exception as exc:
        print(exc)
    
finally:
         y =  np.array(temperature_l)
         x = np.array(time_l)
         plt.title('Temperature measurement')
         plt.ylabel('Temperature (Celsius)')
         plt.xlabel('Time (seconds)')
         plt.plot(x,y)
         plt.show() 
         
         data = np.array([x,y])
         np.save(FILE_PATH,data)    
            
        
                
              
        
                         
    
        
    
            
    
   