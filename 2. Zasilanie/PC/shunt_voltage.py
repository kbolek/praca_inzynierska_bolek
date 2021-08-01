import serial
import time

PORT_NAME = "COM13" 
BAUDRATE  = 9600 
TIMEOUT   = 5

with serial.Serial(PORT_NAME,BAUDRATE,timeout=TIMEOUT) as ser:
            time.sleep(2)
            while True:
                k = input()
                if k == ' ':
                    ser.write('\n'.encode())
                    rx_data =  ser.readline().decode('utf-8').strip()
                    print(rx_data)
                elif k == 'q':
                    break
                 
                    
                
                
                
                
             
            
            
        
        
    

