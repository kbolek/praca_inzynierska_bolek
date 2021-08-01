# -*- coding: utf-8 -*-

import glob, os
import numpy as np
import matplotlib.pyplot as plt

FOLDER_PATH = "R0.1OM/12B_128S_69MS_LSB244UA_DIV4_R0.1OM/data/1000samples"

data_plot = {}

os.chdir(FOLDER_PATH)
for files in glob.glob("*.npy"):
    with open(files ,'rb') as file:
        data = np.load(file) 
        #y_std = np.std(data[1])
        y_mean = np.mean(data[1])
        xlabel = files.rsplit('.',1)[0]
        data_plot.update({str(xlabel+"mA"):y_mean})


ampers = list(data_plot.keys())
mean = list(data_plot.values())


fig = plt.figure(figsize = (12.8,9.6))
plt.grid(b = True, color ='grey',linestyle ='-.', linewidth = 0.5, alpha = 0.2)
plt.ylim(0,1000)
plt.bar(ampers, mean, color='#326DAB',width=0.4)

plt.xlabel("Expected current(mA)")
plt.ylabel("Value of mean measured current (mA)")
plt.title("Meean measured current (R= 0.1 Ω, LSB (max) = 244uA, 128 Samples, 12BIT ADC)",fontsize=14)
plt.show()
   
    
    