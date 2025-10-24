from tkinter import Tk
from ui import MessengerUI

def main():
   root = Tk()
   app= MessengerUI(root)
   root.mainloop()

if __name__ == "__main__":
    main()