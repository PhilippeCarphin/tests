import psutil
import os
#
# This test demonstrates this function which returns the process's memory
# usage in bytes and a loop that creates numpy arrays but without keeping
# references to them (so that loop doesn't make the memory usage grow)
# and another loop that creates arrays and keeps references to them
# (which does make the process memory grow)
#
# Use C-c to end the first loop and go to the second one
#
def get_process_memory_usage():
    process = psutil.Process(os.getpid())
    return process.memory_info().rss

import numpy as np
try:
    i=0
    integers=[]
    memprev = get_process_memory_usage()
    while i < 40000:
        x = np.ones((100,100))
        i = i+1
        # integers.append(i)
        if i%1000 == 0:
            mem = get_process_memory_usage()
            diff = mem - memprev
            print(f"Memory after {i:5} iterations: {get_process_memory_usage()/(1024**2):.4f}MB ({(diff/1000)/(1024**2):.8f}MB per iteration")
            memprev = mem
except KeyboardInterrupt:
    pass

try:
    expected = 100*100*8
    i=0
    arrays = []
    memprev = get_process_memory_usage()
    while True:
        x = np.ones((100,100))
        arrays.append(x)
        i = i+1
        if i%1000 == 0:
            mem = get_process_memory_usage()
            diff = mem - memprev
            print(f"Memory after {i:5} iterations: {get_process_memory_usage()/(1024**2):.2f}MB ({(diff/1000)/(1024**2):.4f}MB per iteration")
            memprev = mem
except KeyboardInterrupt:
    pass
