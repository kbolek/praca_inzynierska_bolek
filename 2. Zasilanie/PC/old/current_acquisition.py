import serial
import sys 
import numpy as np
from matplotlib import pyplot as plt
import pause
from pathlib import Path 
import time

PORT_NAME = "COM13" 
BAUDRATE  = 9600 
TIMEOUT   = 5
PERIOD    =  0.069 #0.069
SAMPLES   = 100

NAME = "GAIN1 - 40mV 100mA LSB_31uA 128S-9ms 12B"

current_l = []
time_l  = []

if Path(NAME+".npy").is_file():
    print("File exsists")   
    sys.exit()
        
try:
        
    with serial.Serial(PORT_NAME,BAUDRATE,timeout=TIMEOUT) as ser:
            print(ser)
            ser.flush()
            pause.seconds(2)
            start_time = time.time()
            for i in range(SAMPLES):
                ser.write('\n'.encode())
               
                rx_data =  ser.readline()#.decode('utf-8')#.rstrip()
                print(i,rx_data)
                
                current_l.append(float(rx_data))   
                print(float(rx_data))
                time_l.append(time.time() - start_time)
                pause.seconds(PERIOD)
                
except Exception as exc:
         print(exc)
    
finally:
          y =  np.array(current_l)
          x = np.array(time_l)
         
          y_std = np.std(y)
          y_mean = np.mean(y)
         
          plt.figure(figsize=(12.8, 9.6))
       
          plt.title("Current measurement (std: {:.3f}, mean: {:.2f}) for ".format(y_std, y_mean) + NAME ,fontsize=17)
          plt.ylabel("Curent (mA)")
          plt.xlabel("Time (seconds)")
          
         
          plt.scatter(x,y)
          plt.show() 
         
#          data = np.array([x,y])
#          np.save(NAME+".npy",data)    
