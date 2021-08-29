import serial
import time

class CurrentSource(serial.Serial):          
    def __init__(self, port_name = "COM2" , baud_rate = 9600, time_out = 5):
        self.port_name = port_name
        self.baud_rate = baud_rate
        self.time_out = time_out     
        
    def __enter__(self):
        super().__init__(self.port_name, self.baud_rate, timeout = self.time_out) 
        self.write('i\n'.encode())
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()
        return True
    
    def current_set(self,current):
        self.write((f'{current/1000:0.3f}'+'\n').encode())
        print(f'{current/1000:0.3f}')
        time.sleep(4)
        
          
if __name__ == '__main__':
    with CurrentSource() as current_source:   
        for current in range(5):
            current_source.current_set(current)
        
            

    
            
            
        
        
        
        

    