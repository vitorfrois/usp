import numpy as np

#define NumPy array
data = np.array([[1,2,3], [4,5,6], [7,8,9], [10, 11, 12], [13, 14, 15]])

#export array to CSV file
np.savetxt("my_data.csv", data, delimiter=",", fmt="%.0f")
