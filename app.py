import subprocess, os
import tkinter as tk
import tkinter.ttk as ttk
from copy import deepcopy

'''
TODO
*CHECKMATE HANDLING
    *ADD CHECK AT BEGINNING OF MAIN_GUI.CPP
    *UPON START SUBROUTINE RUN STDOUT.READLINE
    *IF STRING CONTAINS "CHECKMATE" UPDATE LABEL
    
'''


class Tile(tk.Button):
    def __init__(self, master):
        tk.Button.__init__(self, master)

        self.master = master.master

    def set_attr(self, color, row, col):
        self.configure(bg="black") if color else self.configure(bg="white")
        self.configure(command=self.out, text="   ", relief=tk.FLAT, font=("Segoe UI", 18))

        self.color = color
        self.row = row
        self.col = col

        self.grid(row=row, column=col, sticky=tk.N+tk.S+tk.E+tk.W)

    def out(self):
        if (self.master.piece_to_move != None) and self.isLegal():
            self.master.set_board()
            self.master.piece_to_move.configure(bg="black") if self.master.piece_to_move.color else self.master.piece_to_move.configure(bg="white")
            self.master.check_promotions()
            self.master.piece_to_move = None
        else:
            self.master.piece_to_move = self
            self.master.to_move_label.config(text="Moving piece from %s" % (self.master.col_dict[self.master.piece_to_move.col] + str(8-self.master.piece_to_move.row)))
            self.configure(bg="gray")

    def isLegal(self):
        x1 = self.master.piece_to_move.col
        y1 = self.master.piece_to_move.row
        x2 = self.col
        y2 = self.row

        self.master.call_sub()
        self.master.proc.communicate((self.master.col_dict[x1] + str(8-y1) + "\n").encode() + (self.master.col_dict[x2] + str(8-y2) + "\n").encode())

        self.master.to_move_label.config(text="")
                
        return True

class Promotion_Window(tk.Toplevel):
    def __init__(self, master):
        tk.Toplevel.__init__(self, master)

        self.master = master

    def set_attr(self, pos):
        self.row, self.col = pos[0], pos[1]

        tk.Label(self, text="Promoting \u2659 at " + self.master.col_dict[self.col] + str(8-self.row), font=("Segoe UI", 12)).pack(side=tk.TOP)

        tk.Button(self, text=self.master.convert_unicode("R"), command=lambda: self.promote_to("R"), font=("Segoe UI", 18), relief=tk.RIDGE).pack(side=tk.LEFT)
        tk.Button(self, text=self.master.convert_unicode("N"), command=lambda: self.promote_to("N"), font=("Segoe UI", 18), relief=tk.RIDGE).pack(side=tk.LEFT)
        tk.Button(self, text=self.master.convert_unicode("B"), command=lambda: self.promote_to("B"), font=("Segoe UI", 18), relief=tk.RIDGE).pack(side=tk.LEFT)
        tk.Button(self, text=self.master.convert_unicode("Q"), command=lambda: self.promote_to("Q"), font=("Segoe UI", 18), relief=tk.RIDGE).pack(side=tk.LEFT)

    def promote_to(self, piece):
        self.master.cell_array[self.row][self.col].config(text=self.master.convert_unicode(piece))

        self.master.write_board()
        
        self.destroy()
        

class App(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)

        self.title("chess-ai-acp")

        self.col_dict = {0: "A", 1: "B", 2: "C", 3: "D", 4: "E", 5: "F", 6: "G", 7: "H"}

        ttk.Style().configure('my.TButton', font=('Segoe UI', 12))
        ttk.Button(self, text="Start Over", command=self.reset, style='my.TButton').pack()

        self.to_move_label = tk.Label(self, font=("Segoe UI", 12))
        self.to_move_label.pack()

        self.board_frame = tk.Frame(self)
        self.board_frame.pack()

        self.board_frame.columnconfigure(0, weight=1)
        self.board_frame.rowconfigure(0, weight=1)

        self.piece_to_move = None

        self.cell_array = [[Tile(self.board_frame) for _ in range(8)] for _ in range(8)]

        row_color = True

        for i in range(8):
            for j in range(8):
                self.cell_array[i][j].set_attr(False if j % 2 == 0 else True, i, j) if row_color else self.cell_array[i][j].set_attr(True if j % 2 == 0 else False, i, j)
            row_color = not row_color

        self.set_board()

    def __str__(self):
        output = ""
        for i in range(len(self.cell_array)):
            for j in range(len(self.cell_array[0])):
                output += self.cell_array[i][j]["bg"] + " "
            output += "\n"

        return output

    def call_sub(self):
        self.proc = subprocess.Popen("a ", shell=False, stdout=subprocess.PIPE, stdin=subprocess.PIPE)

    def end_sub(self):
        try:
            subprocess.Popen("TASKKILL /F /PID {pid} /T".format(pid=self.proc.pid))
        except:
            pass

    def reset(self):
        with open("output.txt", "w") as f:
            f.write("R1 N1 B1 Q1 K1 B1 N1 R1 \nP1 P1 P1 P1 P1 P1 P1 P1 \n                        \n                        \n                        \n                        \nP0 P0 P0 P0 P0 P0 P0 P0 \nR0 N0 B0 Q0 K0 B0 N0 R0 ")

        self.set_board()

    def check_promotions(self):
        to_promote = []
        for i in range(8):
            if "\u2659" in self.cell_array[0][i]['text']:
                to_promote.append([0, deepcopy(i)])
            elif "\u2659" in self.cell_array[7][i]['text']:
                to_promote.append([7, deepcopy(i)])
        
        for item in to_promote:
            Promotion_Window(self).set_attr(item)

    def write_board(self):
        output = ""
        for i in range(8):
            for j in range(8):
                if self.cell_array[i][j]['text'].isspace():
                    output += "   "
                else: 
                    output += self.convert_plaintext(self.cell_array[i][j]['text']) + str(0 if self.cell_array[i][j]['fg'] == "red" else 1) + " "
            output += "\n"

        with open("output.txt", "w") as f:
            f.write(output)
            

    def set_board(self):
        board_arr = [["" for _ in range(8)] for _ in range(8)]
        with open("output.txt") as f:
            for i in range(8):
                line = f.readline()
                line = line.replace("\r\n", "").replace("\x0c", "").replace("test", "")
                line = list(map(''.join, zip(*[iter(line)]*3)))
                board_arr[i] = line
                
        for i in range(8):
            for j in range(8):
                self.cell_array[i][j].configure(text=self.convert_unicode(board_arr[i][j][0]), fg=("red" if board_arr[i][j][1] == "0" else "blue"))

    def convert_unicode(self, piece):
        if "R" in piece:
            return "\u2656"
        elif "N" in piece:
            return "\u2658"
        elif "B" in piece:
            return "\u2657"
        elif "Q" in piece:
            return "\u2655"
        elif "K" in piece:
            return "\u2654"
        elif "P" in piece:
            return "\u2659"
        else:
            return "    "

    def convert_plaintext(self, piece):
        if "\u2656" in piece:
            return "R"
        elif "\u2658" in piece:
            return "N"
        elif "\u2657" in piece:
            return "B"
        elif "\u2655" in piece:
            return "Q"
        elif "\u2654" in piece:
            return "K"
        elif "\u2659" in piece:
            return "P"
        else:
            return "    "


if __name__ == '__main__':
    App().mainloop(n=0)