import time
import multiprocessing
import os

tasks = [ 1, 2, 3, 4, 5, 6, 7, 8 ]

def run(task):
    global result_sum
    time.sleep(task)
    print(f"Task {task} done by {os.getpid()}")
    return task**2

with multiprocessing.Pool(4) as p:
    results = p.map(run, tasks)

print(results)
