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
    
    def request_message(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as soc:
            soc.connect((self.server_ip, self.server_port))
            command = "READ_MESSAGES"
            soc.sendall(command.encode())

            buffer = ""
            while True:
                data = soc.recv(512)
                if not data:
                    break
                buffer += data.decode()

        # Split using our delimiter
        raw_messages = buffer.split("-----END-----")

        # Clean messages and remove empties
        messages = [m.strip() for m in raw_messages if m.strip()]

        return messages
    
    # Change the ip
    def change_ip(self, new_ip, new_port=None):
        self.server_ip = new_ip
        if new_port is not None:
            self.server_port = new_port
        print(f"Server changed to: {self.server_ip}:{self.server_port}")
