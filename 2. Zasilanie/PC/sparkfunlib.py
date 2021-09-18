import time

from serialhandler import SerialHandler

class CurrentSource(SerialHandler):          
    def __init__(self):
        super().connect("COM2")
               
    def current_set(self,current):
        if self.ser.is_open == False:
            self.ser.open() 
        uart_str = f'{current/1000:0.3f}'+'\n'
        super().serial_w(uart_str)
        super().exit()
        time.sleep(4)
    
if __name__ == '__main__':
    
    current_source = CurrentSource()
    
    for current in range(20):
        current_source.current_set(current*50)
        print(current)
    
    current_source.exit()
         

        
        
            

    
            
            
        
        
        
        

    