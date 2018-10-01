import socket
import sys

try:
	s = serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	print("Socket created")
except socket.error as err:
	print("Socket failed with error ")


port = 80

try:
	host_ip = socket.gethostbyname('www.google.com')
except socket.gaierror:
	print ("Error resolving host")
	sys.exit()

s.connect((host_ip, port))

print ("The socket has connected to google")
