# -*- coding: utf-8 -*-
import numpy as np
from matplotlib import pyplot as plt


FILE_PATH = './data/SWEEP CURRENT 0-1mA (DC).npy'

with open(FILE_PATH,'rb') as file:
    data = np.load(file)
        
    plt.figure(figsize=(11.8, 9.6))
    plt.title('Current measurement')
    plt.ylabel('Currents by INA219 and Rigol')
    plt.xlabel('Time (seconds)')
   # plt.plot(np.transpose(data), 'p-')
    plt.plot(data[0] - data[1], 'p-')
    plt.show()    

                
           
         