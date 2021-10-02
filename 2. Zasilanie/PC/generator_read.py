import numpy as np

new_dict = np.load("ina219_settings.npy",allow_pickle='TRUE').item()

print(new_dict['40MV_1S_9BIT'])