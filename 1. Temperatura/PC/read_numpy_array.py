import numpy as np
from matplotlib import pyplot as plt


FILE_PATH = 'acquisition.npy'

with open(FILE_PATH,'rb') as file:
    data = np.load(file)
        
    plt.title('Temperature measurement')
    plt.ylabel('Temperature (Celsius)')
    plt.xlabel('Time (seconds)')
    plt.plot(data[0],data[1])
    plt.show()    

                
           
         
     
    