import subprocess, os, copy

import tkinter as tk
import tkinter.ttk as ttk

class Tile(tk.Button):
    def __init__(self, master):
        tk.Button.__init__(self, master)

        self.master = master.master

    def set_attr(self, color, row, col):
        self.row, self.col = row, col

        self.config(fg=color, font=("Segoe UI", 28))

class Promotion_Window(tk.Toplevel):
    def __init__(self, master):
        tk.Toplevel.__init__(self, master)

    def set_attr(self, row, col):
        self.row, self.col = row, col

class App(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)

        self.col_dict = {0: "A", 1: "B", 2: "C", 3: "D", 4: "E", 5: "F", 6: "G", 7: "H"}

    def call_sub(self):
        self.proc = subprocess.Popen("a ", shell=False, stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    
    def end_sub(self):
        try:
            subprocess.Popen("TASKKILL /F /PID {pid} /T".format(pid=self.proc.pid))
        except:
            pass

    def reset(self):
        pass
    
    def check_promotions(self):
        pass

    def read_board(self):
        pass

    def write_board(self):
        pass

    def convert_plaintext(self, piece):
        pass

    def convert_unicode(self, piece):
        pass

if __name__ == "__main__":
    App().mainloop(n=0)