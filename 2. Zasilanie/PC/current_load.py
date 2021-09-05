import serial
import time

class CurrentSource():          
    def __init__(self, port_name = "COM2"):
        self.port_name = port_name
        self.ser = serial.Serial(self.port_name, 9600, timeout = 5)
               
    def current_set(self,current):
        if self.ser.is_open == False:
            self.ser.open()
        
        uart_str = f'{current/1000:0.3f}'+'\n'
        self.ser.write(uart_str.encode())
        self.exit()
        time.sleep(4)
    
    def exit(self):
        self.ser.close()
              
if __name__ == '__main__':
    
    current_source = CurrentSource()
    
    for current in range(20):
        current_source.current_set(current*50)
        print(current)
         

        
        
            

    
            
            
        
        
        
        

    