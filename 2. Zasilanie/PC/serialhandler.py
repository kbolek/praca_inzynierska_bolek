import serial

class SerialHandler(object):
    
    def connect(self, port_name):
         self.port_name = port_name
         self.ser = serial.Serial(self.port_name, 9600, timeout = 5)
         
    def serial_w(self,command):
        self.ser.write(command.encode())
         
    def serial_wr(self,command):
        self.ser.write(command.encode())
        self.serial_read = self.ser.readline().decode('utf-8').strip()
        return self.serial_read
    
    def exit(self):
        self.ser.close()
        