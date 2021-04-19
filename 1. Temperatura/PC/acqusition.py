import serial
import keyboard
import numpy as np
from matplotlib import pyplot as plt
import math
import pause
from pathlib import Path 

if __name__ == "__main__":   
    temperature_samples = []
    port     = "COM5"
    baudrate = 9600
    period   = 0.5
    file_path = 'acquisition.npy'
    try:
        
        if Path(file_path).is_file():
            raise Exception("File exsists")        
              
        with serial.Serial(port,baudrate,timeout = 0.5) as ser:
            while(not keyboard.is_pressed(' ')):
                ser.write('s\n'.encode())
                rx_data =  ser.readline().decode('utf-8').rstrip()
                print(rx_data)
                temperature_samples.append(float(rx_data))   
                pause.seconds(period)
                         
    except Exception as exc:
        print(exc)
        
    finally:
         y =  np.array(temperature_samples)
         x = np.linspace(0,math.ceil(y.size/(1/period)),num=y.size)
         plt.title('Temperature measurement')
         plt.ylabel('Temperature (Celsius)')
         plt.xlabel('Time (seconds)')
         plt.plot(x,y)
         plt.show() 
         
         with open(file_path,'wb') as file:
             data = np.array([x,y])
             np.save(file,data)
            
    
   