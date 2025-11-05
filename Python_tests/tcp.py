import socket
import threading
import sys

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 5447              # Arbitrary non-privileged port
BUFSIZE = 20

def handle_connection(conn, addr):
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(BUFSIZE)

            if not data:
                break

            sys.stdout.buffer.write(f"\n{addr}: DATA: ".encode('UTF-8'))
            sys.stdout.buffer.write(data)
        print('Connection end')


threads = []
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(10)
    while True:
        conn, addr = s.accept()
        t = threading.Thread(target=handle_connection, args=(conn,addr))
        t.start()
        threads.append(t)

