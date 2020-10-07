import numpy as np

for i in range(20):
    x = np.random.rand(10000,10000)
    y = x + x.T
    z = np.sin(y)