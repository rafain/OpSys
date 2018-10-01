# https://medium.com/swlh/lets-write-a-chat-app-in-python-f6783a9ac170
#Rafaín Rodríguez San Millán A01372976

import socket
import threading

clients = {}
addrs = {}

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('HostServer', 8291))

def accept_conections():
    while True:
        client, client_addr = server.accept()
        print("%s:%s has connected." % client_addr)
        client.send(bytes("Welcome to this ultra super secret chat" + "Type your codename and press enter: ", "utf8"))
        addrs[client] = client_addr
        Thread(target=handle_client, args=(client,)).start()

def handle_client(client):
    name = client.recv(1024).decode("utf8")
    welcome = 'Welcome %s! If you want to quito, type "quit" to exit.' % name
    client.send(bytes(welcome, "utf8"))

server.listen(2)
