import serial

class MiliAmperoMeter():          
    def __init__(self, port_name = "COM3"):
        self.port_name = port_name
        self.ser = serial.Serial(self.port_name, 9600, timeout = 5)   
        self.ser.write(':function:current:dc\n'.encode())
        self.current = self.ser.readline().decode('utf-8').strip()
    
    def read_current(self):
        if self.ser.is_open == False:
            self.ser.open()
    
        self.ser.write(':measure:current:dc?\n'.encode())
        self.current = self.ser.readline().decode('utf-8').strip()
        self.exit()
        return self.current
    
    def exit(self):
        self.ser.close()
   
if __name__ == '__main__':
    current_meter =  MiliAmperoMeter() 
    for i in range(5):
            print(current_meter.read_current())
  
        





