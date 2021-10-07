# -*- coding: utf-8 -*-
import numpy as np
from matplotlib import pyplot as plt


FILE_PATH = '320MV_1S_9BIT.npy'

with open(FILE_PATH,'rb') as file:  
    data = np.load(file)
    
    std = np.std(data[0]-data[1])
    vpp = np.max(data[0]-data[1]) - np.min(data[0]-data[1])

    plt.figure(figsize=(12.8, 9.6))
    plt.title('40MV_1S_9BIT 1-100mA (std: {:.3f}, vpp: {:.2f})'.format(std,vpp))
    plt.ylabel("Current measured by INA219 (mA)")
    plt.xlabel("Current measured by Rigol (mA)")
    plt.plot(np.transpose(data), 'p-')
    plt.show()  
    
    plt.figure(figsize=(12.8, 9.6))
    plt.title('40MV_1S_9BIT 1-100mA')
    plt.ylabel("Current measured by INA219 (mA)")
    plt.xlabel("Current measured by Rigol (mA)")
    plt.plot(data[0] - data[1], 'p-')
    plt.show()
    

                
           
         