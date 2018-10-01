import socket

clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientsocket.connect(('localhost', 8291))

input = str(raw_input("Enter a new message to send, or 'q' to exit: "))

while True:
	clientsocket.send(input)
	if (input == 'q'):
		print("Quitting.")
		break
	
	input = str(raw_input("Enter a new message to send, or 'q' to exit: "))

clientsocket.close()