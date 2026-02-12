
import time
import multiprocessing
import os

class Task:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c
    def run(self):
        print(f"Worker PID: {os.getpid()}, doing something with a={self.a}, b={self.b}, c={self.c}")
        return self
        # return f"{self.a}-{self.b}-{self.c}"

def generate_tasks(n):
    for i in range(n):
        yield Task(i, i**2, i**3)


with multiprocessing.Pool(4) as p:
    results = p.map(Task.run, generate_tasks(8))

print(results)
