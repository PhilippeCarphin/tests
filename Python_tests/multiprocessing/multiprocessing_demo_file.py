import time
import multiprocessing
import os
import subprocess

tasks = open("tasks.sh", 'r').read().splitlines()
result_sum = 0

def run(task):
    subprocess.run(task, shell=True)

with multiprocessing.Pool(4) as p:
    results = p.map(run, tasks)

