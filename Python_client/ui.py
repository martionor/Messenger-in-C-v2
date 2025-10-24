import tkinter as tk
from tkinter import messagebox, simpledialog
from tkinter import messagebox
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

        #Buttons
        tk.Button(root, text="Send Message", command=self.send_message).grid(row=3, column=0, sticky="e")
        tk.Button(root, text="Read Messages", command=self.read_messages).grid(row=3, column=1, sticky="e")


    def send_message(self):
        sender = self.sender_entry.get()
        recipient= self.recipient_entry.get()
        subject=  self.message_entry.get("1.0", tk.END).strip()
        msg= Message(sender, recipient, subject)
        self.client.send_message(msg)
        messagebox.showinfo("Info", "Message sent")

    def read_messages(self):
        password = simpledialog.askstring("Password", "Enter password: ")
        if password:
            messages = self.client.request_message(password)

            if len(messages)== 0:
                messagebox.showinfo("Messages", "No messages found.")
            else:
                messagebox.showinfo("Messages", "\n\n".join(messages))
