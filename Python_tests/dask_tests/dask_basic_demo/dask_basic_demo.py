import psutil
import os
bytes_per_mb = 10**6
def bytes_to_mb(n_bytes):
    return n_bytes / bytes_per_mb
def memory_usage():
    process = psutil.Process(os.getpid())
    return f'{bytes_to_mb(process.memory_info().rss)}MB'
def show_memory_usage():
    print(f"Current memory usage: {memory_usage()}")
def wait_for_return_key():
    input("Press Enter key to advance in the program")
def stall_at_end():
    input("Stalling at end of program, press Enter to terminate")


import webbrowser
print("Example : https://examples.dask.org/array.html#Start-Dask-Client-for-Dashboard with added automation")

# Section 'Create Client for Dashboard'
import time
from dask.distributed import Client, progress
client = Client(processes=False, threads_per_worker=4,
                n_workers=1, memory_limit='2GB')

print(f'Created dask.distributed.Client object, dashboard link is {client.dashboard_link}')
print("Opening dask dashboard")
webbrowser.open(client.dashboard_link)

# Section 'Create Random array'
show_memory_usage()
print("Creating big random dask array")
import dask.array as da
x = da.random.random((10000, 10000), chunks=(1000, 1000))
print(f'Created x, a random dask.array: {x}')
show_memory_usage()
print(f'(10000x10000 float64 would take up 800MB) so x has not yet been materialized')
print("Arranging a computation y = x + x.T, z = da.sin(y)")
y = x + x.T
z = da.sin(y)
print(f'y : {y}')
print(f'z : {z}')
print("Now type real_z = z.compute() and watch the dashboard in your browser")