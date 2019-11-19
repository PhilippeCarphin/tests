
import os

import subprocess

import sys


from paramiko import SSHClient
from scp import SCPClient

class ScpWrapper():
    def __init__(self, host, port):
        self.scp = None
        self.ssh = SSHClient()
        self.ssh.load_system_host_keys()
        self.ssh.connect(host, port=port)
        self.scp = SCPClient(self.ssh.get_transport())

    def __del__(self):
        if self.scp: self.scp.close()

if __name__ == "__main__":
    scpr = ScpWrapper(host="96.21.220.145", port=5446)
    scpr.scp.put(os.path.expanduser('~/.bashrc'), remote_path='/Users/pcarphin/Desktop')


