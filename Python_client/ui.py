import tkinter as tk
from tkinter import messagebox, simpledialog, scrolledtext
from client import MessengerClient
from message import Message

class MessengerUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Messenger")
        self.client = MessengerClient()

        #Sender
        tk.Label(root, text="Your name:").grid(row=0,column=0)
        self.sender_entry = tk.Entry(root)
        self.sender_entry.grid(row=0, column=1)

        #Recipient
        tk.Label(root, text="To:").grid(row=1, column=0)
        self.recipient_entry = tk.Entry(root)
        self.recipient_entry.grid(row=1, column=1)

        #Message box
        tk.Label(root, text="Message subject:").grid(row=2,column=0)
        self.message_entry=tk.Text(root, height=5, width=40)
        self.message_entry.grid(row=2, column=1)

        #Ip and Port change
        tk.Label(root, text="Server IP:").grid(row=3, column=0)
        self.ip_entry= tk.Entry(root)
        self.ip_entry.insert(0, self.client.server_ip)
        self.ip_entry.grid(row=3, column=1)

        tk.Label(root, text="Port").grid(row=4, column=0)
        self.port_entry=tk.Entry(root)
        self.port_entry.insert(0, self.client.server_port)
        self.port_entry.grid(row=4, column=1)

        tk.Button(root, text="Change server", command= self.change_server).grid(row=4, column=0)

        #Buttons
        tk.Button(root, text="Send Message", command=self.send_message).grid(row=4, column=1, sticky="e")
        # tk.Button(root, text="Read Messages", command=self.read_messages).grid(row=5, column=1, sticky="e")

        #Real-time messages
        tk.Label(root, text="Messages:").grid(row=6, column=0, columnspan=3)
        self.message_display = scrolledtext.ScrolledText(root, height=10, width=60, state="disabled")
        self.message_display.grid(row=7, column=0, columnspan=3)

        self.auto_refresh()

    def send_message(self):
        sender = self.sender_entry.get()
        recipient= self.recipient_entry.get()
        subject=  self.message_entry.get("1.0", tk.END).strip()
        msg= Message(sender, recipient, subject)
        self.client.send_message(msg)
        messagebox.showinfo("Info", "Message sent")

    def read_messages(self):
            messages = self.client.request_message()

            self.message_display.config(state="normal")
            self.message_display.delete("1.0", tk.END)


            for msg in messages:
                self.message_display.insert(tk.END, msg + "\n")
            self.message_display.config(state="disabled")
            
    
    def change_server(self):
         new_ip = self.ip_entry.get().strip()
         new_port = int(self.port_entry.get().strip())
         self.client.change_ip(new_ip, new_port)
         messagebox.showinfo("Info", f"Server changed to {new_ip}:{new_port}")

    def auto_refresh(self):
        self.read_messages()
        self.root.after(2000, self.auto_refresh) #every 2 second refresh