# -*- coding: utf-8 -*-
import numpy as np
from matplotlib import pyplot as plt


FILE_PATH = '1000_samples_500mA_period_128ms_128S.npy'

with open(FILE_PATH,'rb') as file:
    data = np.load(file)
        
    plt.figure(figsize=(12.8, 9.6))
    plt.title('Current measurement')
    plt.ylabel('Current (Amper)')
    plt.xlabel('Time (seconds)')
    plt.scatter(data[0],data[1])
    plt.show()    

                
           
         