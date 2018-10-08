#Name1: Rafaín Rodríguez San Millán A01372976
#Name2: Lenin Silva Gutierrez A01373214
#
# Client code for encrypted chat

import socket
import threading as THR

def receive(key):
    while True:
        try:
            msg = client_socket.recv(1024)
            msg = msg.split("{s}")
            if len(msg) == 1:
                msg[0] = decrypt_stream(msg[0],key)
            print(msg[0])
        except OSEroor:   #Trouble
            break

def send(key, name):
    
    client_socket.send(name)
    while True:
        msg = str(raw_input())
        if msg == "{q}":
            client_socket.send(msg)
            client_socket.close()
            break
        else:
            msg = encrypt_stream(name + ": " + msg, key)
            client_socket.send(msg)

def encrypt_stream(data, key):
    encrypted = ""
    for char in data:
        encrypted += chr(ord(char)^key)
    return encrypted

def decrypt_stream(data, key):
    decrypted = ""
    for char in data:
        decrypted += chr(ord(char)^key)
    return decrypted

def main():
    key = int(input("Enter the key: "))
    name = raw_input("Welcome to this ultra super secret chat. Type your codename and press enter: ")
    receive_thread = THR.Thread(target=receive, args= (key,))
    send_thread = THR.Thread(target=send, args = (key,name,))

    receive_thread.start()
    send_thread.start()

    receive_thread.join()
    send_thread.join()



HOST = 'localhost'
port = 8291


client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, port))

main()
