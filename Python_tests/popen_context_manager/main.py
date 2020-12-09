import time
import subprocess


with subprocess.Popen(['tail -f ~/log.txt'], shell=True) as p:
    while True:
        time.sleep(5)


