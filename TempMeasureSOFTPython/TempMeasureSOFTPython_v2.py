import serial
import keyboard
import sys

if __name__ == "__main__":
    
    port = str(sys.argv[1])
    baudrate = int(sys.argv[2])
    
    usart = serial.Serial(port,baudrate,timeout = 0.12) 
    usart.reset_input_buffer()
     
    while(True):
        if keyboard.is_pressed(' '):
            usart.close()     
            break
        else:
            rx_data = usart.readline()
            if rx_data:
                rx_data = rx_data.decode()[:-2]
                print(rx_data)   
            