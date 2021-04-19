import numpy as np

if __name__ == "__main__":  
    file_path = 'acquisition.npy'
    with open(file_path,'rb') as file:
        x = np.load(file)
        print(x)
         
           
         
     
    