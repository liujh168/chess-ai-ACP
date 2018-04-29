import tkinter as tk
import tkinter.ttk as ttk
import subprocess, os, copy, time

'''
TODO
*IMPLEMENT PROMOTION SUBWINDOW
    *CHECK FOR PAWNS WHERE ROW=0,8
    *DIRECTLY EDIT OUTPUT.TXT
*CHECKMATE HANDLING
    *ADD CHECK AT BEGINNING OF MAIN_GUI.CPP
    *UPON START SUBROUTINE RUN STDOUT.READLINE
    *IF STRING CONTAINS "CHECKMATE" UPDATE LABEL
'''


class Tile(tk.Button):
    def __init__(self, master):
        tk.Button.__init__(self, master)

        self.master = master.master

        self.col_dict = {0: "A", 1: "B", 2: "C", 3: "D", 4: "E", 5: "F", 6: "G", 7: "H"}

    def set_attr(self, color, row, col):
        self.configure(bg="black") if color else self.configure(bg="white")
        self.configure(command=self.out, text="   ", relief=tk.FLAT)
        self.configure(font=("Segoe UI", 14))

        self.color = color
        self.row = row
        self.col = col

        self.grid(row=row, column=col)

    def out(self):
        if (self.master.piece_to_move != None) and self.isLegal():
            self.master.set_board()
            self.master.piece_to_move.configure(bg="black") if self.master.piece_to_move.color else self.master.piece_to_move.configure(bg="white")
            self.master.piece_to_move = None
        else:
            self.master.piece_to_move = self
            self.master.to_move_label.config(text="moving piece from %s" % (self.col_dict[self.master.piece_to_move.col] + str(8-self.master.piece_to_move.row)))
            self.configure(bg="gray")

    def isLegal(self):
        x1 = self.master.piece_to_move.col
        y1 = self.master.piece_to_move.row
        x2 = self.col
        y2 = self.row

        self.master.call_sub()

        moves = [(self.col_dict[x1] + str(8-y1) + "\n").encode(), (self.col_dict[x2] + str(8-y2) + "\n").encode()]

        self.master.proc.communicate(moves[0] + moves[1])
        self.master.to_move_label.config(text="")
        
        return True

class App(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)


        self.title("chess-ai-acp")
        board_arr = [["" for _ in range(8)] for _ in range(8)]

        self.reset_button = ttk.Button(self, text="Start Over", command=self.reset)
        self.reset_button.pack()

        self.to_move_label = tk.Label(self)
        self.to_move_label.pack()

        self.board_frame = tk.Frame(self)
        self.board_frame.pack()

        with open("output.txt") as f:
            for i in range(8):
                line = f.readline()
                line = line.replace("\r\n", "").replace("\x0c", "").replace("test", "")
                line = list(map(''.join, zip(*[iter(line)]*3)))
                board_arr[i] = line

        self.place_toggle = False
        self.piece_to_move = None

        self.cell_array = [[Tile(self.board_frame) for _ in range(8)] for _ in range(8)]

        row_color = True

        for i in range(8):
            for j in range(8):
                if board_arr[i][j] == "":
                    board_arr[i][j] = "  "
                if j % 2 != 0:
                    self.cell_array[i][j].set_attr(True, i , j) if row_color else self.cell_array[i][j].set_attr(False, i, j)
                    self.cell_array[i][j].configure(text=" " + self.convert_unicode(board_arr[i][j][0]) + " ", fg=("red" if board_arr[i][j][1] == "0" else "blue"))
                    
                else:
                    self.cell_array[i][j].set_attr(False, i, j) if row_color else self.cell_array[i][j].set_attr(True, i, j)
                    self.cell_array[i][j].configure(text=" " + self.convert_unicode(board_arr[i][j][0]) + " ", fg=("red" if board_arr[i][j][1] == "0" else "blue"))
            row_color = not row_color

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
        subprocess.Popen("TASKKILL /F /PID {pid} /T".format(pid=self.proc.pid))

    def reset(self):
        with open("output.txt", "w") as f:
            f.write("R1 N1 B1 Q1 K1 B1 N1 R1 \nP1 P1 P1 P1 P1 P1 P1 P1 \n                        \n                        \n                        \n                        \nP0 P0 P0 P0 P0 P0 P0 P0 \nR0 N0 B0 Q0 K0 B0 N0 R0 ")
            f.close()

        self.set_board()

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
                self.cell_array[i][j].configure(text=" " + self.convert_unicode(board_arr[i][j][0]) + " ", fg=("red" if board_arr[i][j][1] == "0" else "blue"))

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


if __name__ == '__main__':
    os.chdir(os.path.dirname(os.path.realpath(__file__)))
    a = App()
    a.mainloop(n=0)