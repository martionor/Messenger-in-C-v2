class Message:
    def __init__(self, sender, recipient, subject):
        self.sender = sender
        self.recipient = recipient
        self.subject = subject

    def __str__(self):
        return f"From:{self.sender}\nTo: {self.recipient}\nMessage: {self.subject}"