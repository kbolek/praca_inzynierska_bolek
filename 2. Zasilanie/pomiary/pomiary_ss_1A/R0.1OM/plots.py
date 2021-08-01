# -*- coding: utf-8 -*-

import glob, os
import numpy as np
import matplotlib.pyplot as plt

CATALOG = "C:/Users/bolko/Desktop/pomiary_ss_1A/R0.1OM/new_screens/"
FOLDER_PATH = "diff_BIT_1S_500mA_LSB31UA_DIV32_R0.1OM/data"

os.chdir(FOLDER_PATH)
for files in glob.glob("*.npy"):
    with open(files ,'rb') as file:
        name =files.rsplit('.',1)[0]
        data = np.load(file) 
   
        plt.figure(figsize=(12.8, 9.6))
        plt.title('Current measurement' + ' ' + name)
        plt.ylabel('Current (Amper)')
        plt.xlabel('Time (seconds)')
        plt.scatter(data[0],data[1])
        plt.savefig(CATALOG+name+'.png', bbox_inches='tight')






   