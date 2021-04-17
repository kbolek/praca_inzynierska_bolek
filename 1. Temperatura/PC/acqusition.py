import serial
import serial.tools.list_ports
import keyboard

if __name__ == "__main__":    
    try:
        port = "COM5"
        baudrate = 9600
        with serial.Serial(port,baudrate,timeout = 0.5) as ser:
            while(not keyboard.is_pressed(' ')):
                ser.write('s\n'.encode())
                rx_data =  ser.readline().decode('utf-8').rstrip()
                print(rx_data)   
                
    except Exception as exc:
        print(exc)
    

    
   