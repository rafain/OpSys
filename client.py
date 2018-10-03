import socket
import threading as THR

def receive():
    while True:
        try:
            msg = client_socket.recv(1024)
            print(msg)
        except OSEroor:   #Trouble
            break

def send(event=None):
    while True:
        msg = str(raw_input(""))
        client_socket.send(msg)
        if msg == "quit":
            client_socket.close()

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

def init():
    i=0
    msg = ""
    while i<2:
        try:
            msg = client_socket.recv(1024)
            print(msg)
            i += 1
        except OSEroor:   #Trouble
            break
    return msg.split(" ")


HOST = 'localhost'
port = 8291


client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, port))


key = int(raw_input("Type in your key: "))

receive_thread = THR.Thread(name = "r", target=receive)
receive_thread.start()

send_thread = THR.Thread(name = "s",target=send)
send_thread.start()

