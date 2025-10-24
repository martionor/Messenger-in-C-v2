import socket

server_ip="127.0.0.1"
server_port = 8080
class MessengerClient:
    def __init__(self, ip=server_ip, port=server_port):
        self.server_ip = ip
        self.server_port= port

    def send_message(self, message):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as soc:
            soc.connect((self.server_ip, self.server_port))
            soc.sendall(str(message).encode())
            print("Message sent")
    
    def request_message(self, password):
        messages = []

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as soc:
            soc.connect((self.server_ip, self.server_port))
            command = f"READ_MESSAGES:{password}"
            soc.sendall(command.encode())

            print("Messages on server:")
            while True:
                data = soc.recv(512)
                if not data:
                    break
                messages_received= True
                print(data.decode())
                messages.append(data.decode().strip())

        if not messages_received:
            print("No messages on server.")
        return messages