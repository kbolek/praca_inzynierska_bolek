# -*- coding: utf-8 -*-
"""
The software is made by Krzysztof Bolek AGH MTM EAIIIB. All rights reserved. 
"""

import serial
import serial.tools.list_ports
import numpy as np
import keyboard

class SerialConnection(object):
    def __init__(self):
         self.timeout = 0.12
         print("Choose the UART settings for connection: \n")
    
    def choose(self,data_arr,data_string):
        self.data_arr = data_arr
        self.data_string = data_string
        
        print(self.data_string+"\n")
        for number,self.element in enumerate(self.data_arr):
            print((number+1),".",self.element)
        
        self.chosed_element = input("Enter the number:")
        if (int(self.chosed_element) > 0) and (int(self.chosed_element) < (self.data_arr.size + 1)):
            print("Good choice!")
            return data_arr[int(self.chosed_element)-1]
        else:
            print("You have to choose the appriopriate number!\n")
            self.choose(self.data_arr,self.data_string)
    
    def disconnect(self):
        try:
            self.usart.close()
        except:
            print("Error: could not close the port")
            
    
    def connect(self,port,baud_rate):
        self.port_full_name = str(port)
        self.baud_rate = baud_rate
        
        
        self.get_only_port = self.port_full_name.find("COM")
        self.port = self.port_full_name[self.get_only_port:self.get_only_port+4]
        
        try:
            self.usart = serial.Serial(self.port,self.baud_rate,timeout = self.timeout)  
            self.usart.reset_input_buffer()
            print("You connect with the serial!")
            
   
        except serial.serialutil.SerialException:
            print("An error occured during the connecting with serial")
            self.disconnect(self.usart)
    
    
    def read_the_data(self):
        self.rx_data =  self.usart.readline()
        if self.rx_data:
            self.rx_data = self.rx_data.decode()[:-2]
            print(self.rx_data)            
                      

if __name__ == "__main__":
    #**********THE CONNECTION WITH THE UART**********
    serial_set_obj = SerialConnection()
    
    ports = np.array(serial.tools.list_ports.comports())
    ports_str = "Choose the COM port (by writing the number):"
    port_full_name = serial_set_obj.choose(ports, ports_str)
    
    baud_rates = np.array([9600,14400,19200,38400,57600,115200,128000])
    baud_rates_str = "Choose the baud rate (by writing the number):"
    baud_rate = serial_set_obj.choose(baud_rates, baud_rates_str)
    
    serial_set_obj.connect(port_full_name, baud_rate)
    
     #**********THE COLLECTING DATA**********
    print("If you want to dissconect with serial and save the data press space")
    
    while(True):
        if keyboard.is_pressed(' '):
            print("The software ended collecting the data")
            serial_set_obj.disconnect()
            break
        else:
             serial_set_obj.read_the_data()
            
            


    
    
   
    