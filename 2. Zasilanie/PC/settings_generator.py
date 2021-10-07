import numpy as np
import sys
from pathlib import Path 


NAME = "ina219_settings.npy"

if Path(NAME).is_file():
    print("File exsists")   
    sys.exit()
    

GAIN    =  {"40MV":0x0000, "80MV":0x0800, "160MV":0x1000, "320MV": 0x1800}
BITS    =  {"1S_9BIT":0x0000, "1S_10BIT":0x0080, "1S_11BIT": 0x0100, "1S_12BIT":0x0180}
SAMPLES =  {"2S_12BIT": 0x480, "4S_12BIT": 0x0500, "8S_12BIT":0x0580, "16S_12BIT": 0x0600,
            "32S_12BIT": 0x0680,"64S_12BIT":0x0700, "128S_12BIT":0x0780}
MODE_SANDBVOLT_CONTINOUS = 0x07


data = {}

for gain_mask in GAIN:
    for bits_mask in BITS:
        data.update({gain_mask+"_"+bits_mask : GAIN[gain_mask]| BITS[bits_mask] | (BITS[bits_mask] >> 4) | MODE_SANDBVOLT_CONTINOUS })

for gain_mask in GAIN:
    for bits_mask in SAMPLES:
        data.update({gain_mask+"_"+bits_mask : GAIN[gain_mask]| SAMPLES[bits_mask] | (SAMPLES[bits_mask] >> 4) | MODE_SANDBVOLT_CONTINOUS})
           

np.save(NAME,data)