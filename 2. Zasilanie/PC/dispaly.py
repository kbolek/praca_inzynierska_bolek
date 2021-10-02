# -*- coding: utf-8 -*-
import numpy as np
from matplotlib import pyplot as plt


FILE_PATH = './CORNER_SETTINGS.npz'
corner_settings = ['40MV_1S_9BIT','40MV_1S_12BIT','40MV_128S_12BIT','320MV_1S_9BIT', '320MV_1S_12BIT', '320MV_128S_12BIT']


with open(FILE_PATH,'rb') as file:
    data = np.load(file)

    for count in range(len(data['title'])):
          plt.figure(figsize=(11.8, 9.6))
          plt.title('Current measurement for ' + data['title'][count])
          plt.ylabel('Currents by INA219 and Rigol')
          plt.xlabel('Time (seconds)')
          plt.plot(data['x'],data['y'][count])
          #plt.plot(data['x'] - data['y'][count], 'p-')
          plt.show()   
        
    
    
    

                
           
         