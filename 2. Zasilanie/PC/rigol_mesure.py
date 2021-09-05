import serial
import time

class MiliAmperoMeter(serial.Serial):          
    def __init__(self, port_name = "COM3" , baud_rate = 9600, time_out = 5):
        self.port_name = port_name
        self.baud_rate = baud_rate
        self.time_out = time_out     
        
    def __enter__(self):
        super().__init__(self.port_name, self.baud_rate, timeout = self.time_out) 
        self.write(':function:current:dc\n'.encode())
        self.current = self.readline().decode('utf-8').strip()
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()
        return True
    
    def read_current(self):
        self.write(':measure:current:dc?\n'.encode())
        self.current = self.readline().decode('utf-8').strip()
        return self.current
              
if __name__ == '__main__':
    with MiliAmperoMeter() as current_meter:   
        for i in range(5):
            print(current_meter.read_current())
            time.sleep(1)





