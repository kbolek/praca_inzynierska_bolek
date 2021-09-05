import serial
import time

class CurrentSource(serial.Serial):          
    def __init__(self, port_name = "COM2" , baud_rate = 9600, time_out = 5, write_timeout = 1):
        self.port_name = port_name
        self.baud_rate = baud_rate
        self.time_out = time_out     
        
    def __enter__(self):       
        super().__init__(self.port_name, self.baud_rate, timeout = self.time_out) 
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()
        return True
    
    def current_set(self,current):
        uart_str = f'{current/1000:0.3f}'+'\n'
        self.write(uart_str.encode())
        self.reset_input_buffer()
        time.sleep(4)
        
    def current_reset(self):
        self.write(('r\n').encode())
                     
if __name__ == '__main__':
    with CurrentSource() as current_source: 
        current_source.current_set(10)
        for current in range(20):
            current_source.current_set(current*50)
            print(current)
            
         
        
            

    
            
            
        
        
        
        

    