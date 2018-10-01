import socket

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind(('localHost', 8291))
serversocket.listen(5)

connection, address = serversocket.accept()


while True:
	
	buf = connection.recv(64)
	if (buf == 'q'):
		print("Quitting")
		break 
	print("Recived: " + buf)
	print("To quit send 'q'")

serversocket.close()