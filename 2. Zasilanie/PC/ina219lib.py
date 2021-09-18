import time

from serialhandler import SerialHandler

class INA219(SerialHandler):          
    def __init__(self):
        super().connect("COM6")
        time.sleep(2)
        
    def read_current(self):
       return super().serial_wr('cr\r')
    
    def callib(self,value):
       return super().serial_wr("cc " + str(value) + "\r")
              
if __name__ == '__main__':
    ina = INA219()
    
    ina.callib(100)
    for i in range(5):
        print(ina.read_current())
        time.sleep(0.5)        
         
    ina.exit()

    