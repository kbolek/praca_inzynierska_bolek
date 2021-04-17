import serial
import serial.tools.list_ports
import keyboard
 

if __name__ == "__main__": 
    ports = iter(list(serial.tools.list_ports.comports()))
    while True:
        try:
            port = next(ports)
            if "Arduino" in str(port):
                port = str(port)[:5]
                #port = next((str(port)[:4] for port in list(serial.tools.list_ports.comports()) if "Arduino Micro" in str(port)),None)
            baudrate = 9600
            with serial.Serial(port,baudrate,timeout = 0.5) as ser:
                while(not keyboard.is_pressed(' ')):
                    ser.write('s\n'.encode())
                    rx_data =  ser.readline().decode('utf-8').rstrip()
                    print(rx_data) 
            break          
        except serial.SerialException:
            continue
        
        except Exception as exc:
            print(exc)
        break
     
  
    
   