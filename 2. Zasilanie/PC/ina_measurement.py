import serial
import time

class INA219(serial.Serial):          
    def __init__(self, port_name = "COM4" , baud_rate = 9600, time_out = 5):
        self.port_name = port_name
        self.baud_rate = baud_rate
        self.time_out = time_out          
    def __enter__(self):
        super().__init__(self.port_name, self.baud_rate, timeout = self.time_out) 
        time.sleep(2)
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()
        return True
    
    def read_current(self):
        self.write('cr\r'.encode())
        self.current = self.readline().decode('utf-8').strip()
        return self.current
    
    def callib(self,value):
        self.write(("cc " + str(value) + "\r").encode())
        self.current = self.readline().decode('utf-8').strip()
        print(self.current)
              
if __name__ == '__main__':
    with INA219() as ina:
        for i in range(5):
            ina.read_current()

    