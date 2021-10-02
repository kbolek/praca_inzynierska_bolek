from serialhandler import SerialHandler

class MiliAmperoMeter(SerialHandler):          
    def __init__(self):
        super().connect("COM3")
        super().serial_wr(':function:current:dc\n')
    
    def read_current(self):
        if self.ser.is_open == False:
            self.ser.open()   
        self.current = super().serial_wr(':measure:current:dc?\n')
        super().exit()
        if self.current[1:] != 'E':
            return float(self.current[1:])*1000
        else:
            return self.read_current()
            
if __name__ == '__main__':
    current_meter =  MiliAmperoMeter() 
    for i in range(100):
            print(current_meter.read_current())
  
        