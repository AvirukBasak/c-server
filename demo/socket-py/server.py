#!/bin/env python

import socket     # socket functions
import sys        # system functions
import signal     # signal handling
import readline   # richer input

SOCK_BACKLOG = 1     # accept one connection at a time
RECV_SIZE    = 4096  # max length of recieved data

def server(port = 8080):
    while True:
        host = socket.gethostname()
        srv_sock = socket.socket()
        srv_sock.bind((host, port))
        print('server: {}:{}: waiting for client'.format(host, port))
        srv_sock.listen(SOCK_BACKLOG)
        (conn, address) = srv_sock.accept()  # accept new connection
        print('server: {}:{}: client connected'.format(address[0], address[1]))
        while True:
            data = str(conn.recv(RECV_SIZE).decode())
            if not data:
                print('server: {}:{}: client closed connection'.format(address[0], address[1]))
                break
            print('[{}:{}]: {}'.format(address[0], address[1], data))
            data = input('[you]: ')
            conn.send(data.encode())
        conn.close()

if __name__ == '__main__':
    signal.signal(signal.SIGINT, lambda sig, frame: sys.exit(0))
    if len(sys.argv) < 2:
        server()
    else:
        server(sys.argv[1])
