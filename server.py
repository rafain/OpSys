#https://medium.com/swlh/lets-write-a-chat-app-in-python-f6783a9ac170

import socket
import threading as THR

clients = {}
addrs = {}

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 8291))

def accept_conections():
    while True:
        client, client_addr = server.accept()
        print("%s:%s has connected." % client_addr)
        client.send("Welcome to this ultra super secret chat. Type your codename and press enter: ")
        addrs[client] = client_addr
        THR.Thread(target=handle_client, args=(client,)).start()

def handle_client(client):
    name = client.recv(1024)
    welcome = 'Welcome %s! If you want to quit, type "quit" to exit.' % name
    client.send(welcome)
    clients[client] = name
    while True:
        msg = client.recv(1024)
        if msg !=  "quit":
            broadcast(msg, name+ ": ")
        else:
            client.send("quitting")
            client.close()
            del clients[client]
            broadcast("%s has left the chat." % name)
            break

def broadcast(msg, prefix=""):
    for sock in clients:
        sock.send(prefix + msg)


def main():
    server.listen(4)
    print("Waiting for connection...")
    ACCEPT_THREAD = THR.Thread(target=accept_conections)
    ACCEPT_THREAD.start()
    ACCEPT_THREAD.join()
    server.close()

main()
