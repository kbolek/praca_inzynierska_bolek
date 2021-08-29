import time
from current_load import CurrentSource
from rigol_mesure import MiliAmperoMeter
from ina_measurement import INA219

try:
    with CurrentSource() as current_source, \
         MiliAmperoMeter() as current_meter, \
         INA219() as ina: 
             #Calibration
             current_source.current_set(100)
             I = float(current_meter.read_current()[1:])*1000
             print(I)
             ina.callib(I)
             
             #Acquisition
             for i in range(5):
                 current_source.current_set(i*100)
                 I = ina.read_current()
                 time.sleep(2)
                 print(I)                                    
        
except Exception as exc:
    print(exc)
                  
