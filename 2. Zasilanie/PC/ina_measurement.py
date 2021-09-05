import serial
import time

class INA219():          
    def __init__(self, port_name = "COM6"):
        self.port_name = port_name
        self.ser = serial.Serial(self.port_name, 9600, timeout = 5)
        time.sleep(2)
    
    def read_current(self):
        self.ser.write('cr\r'.encode())
        self.current = self.ser.readline().decode('utf-8').strip()
        return self.current
    
    def callib(self,value):
        self.ser.write(("cc " + str(value) + "\r").encode())
        self.current = self.ser.readline().decode('utf-8').strip()
    
    def exit(self):
        self.ser.close()
              
if __name__ == '__main__':
    ina = INA219()
    for i in range(5):
        print(ina.read_current())
        time.sleep(0.5)        
    ina.exit()
            
        

    