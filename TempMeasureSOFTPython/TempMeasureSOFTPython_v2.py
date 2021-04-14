import serial
import keyboard
import sys

if __name__ == "__main__":
    
    port = str(sys.argv[1])
    baudrate = int(sys.argv[2])
    
    try:
        usart = serial.Serial(port,baudrate,timeout = 5)
        usart.reset_input_buffer()
              
        while(not keyboard.is_pressed(' ')):
                usart.write('s'.encode())
                rx_data =  usart.readline().decode('utf-8').rstrip()
                print(rx_data)            
        usart.close() 
                
    except serial.serialutil.SerialException as serial_err:
        print("An error: {0} occured during establishing connection with microcontroller".format(serial_err))
    
    except serial.SerialTimeoutException as timeout_err:
        print("An timeout error: {0} occured - the time is exceeded ".format(timeout_err))
           
    except:
        print("Unexpected error:", sys.exc_info()[0])
        
        
    
  