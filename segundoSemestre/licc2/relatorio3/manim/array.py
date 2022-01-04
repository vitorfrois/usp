import numpy as np

#define NumPy array
data = np.array(
    [[100,1000,5000,10000,20000], 
    [1,2,3,20,25], 
    [4,5,6,30,15], 
    [7,8,9,20,10]])

#export array to CSV file
np.savetxt("my_data.csv", data, delimiter=",", fmt="%.0f")
