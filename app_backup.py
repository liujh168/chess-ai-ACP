import tkinter as tk

import subprocess, os, copy, time
from tempfile import SpooledTemporaryFile as tempfile

class Tile(tk.Button):
    def __init__(self, master):
        tk.Button.__init__(self, master)

        self.master = master

        self.col_dict = {0: "A", 1: "B", 2: "C", 3: "D", 4: "E", 5: "F", 6: "G", 7: "H"}

    def set_attr(self, color, row, col):
        self.configure(bg="black") if color else self.configure(bg="white")
        self.configure(command=self.out, text="   ")

        self.color = color
        self.row = row
        self.col = col

        self.grid(row=row, column=col)

    def out(self):
        self.master.place_toggle = not self.master.place_toggle
        
        if (self.master.piece_to_move != None) and self.isLegal():
            #temp = copy.deepcopy(self.master.piece_to_move['text'])

            #self.master.piece_to_move['text'] = self['text']
            #self['text'] = temp

            self.master.set_board()

            self.master.piece_to_move = None
        else:
            self.master.piece_to_move = self


        print(self.row, ", ", self.col, ", ", self.color)
    
    def isLegal(self):
        x1 = self.master.piece_to_move.col
        y1 = self.master.piece_to_move.row
        x2 = self.col
        y2 = self.row

        moves = [(self.col_dict[x1] + str(8-y1) + "\n").encode(), (self.col_dict[x2] + str(8-y2) + "\n").encode()]
        print(moves[0], moves[1])
        self.master.proc.stdin.write(moves[0])
        time.sleep(1)
        self.master.proc.stdin.write(moves[1])

        #print("piece to move: " + self.col_dict[x1] + str(8-y1))
        #print("where to move: " + self.col_dict[x2] + str(8-y2) + "\n")
        
        return True

class App(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)

        self.proc = subprocess.Popen("a ", shell=True, stdout=subprocess.PIPE, stdin=subprocess.PIPE)

        board_arr = [["" for _ in range(8)] for _ in range(8)]
        with open("output.txt") as f:
            for i in range(8):
                line = f.readline()
                print(line)
                line = line.replace("\r\n", "").replace("\x0c", "").replace("test", "")
                line = line.split(" ")[:-1]

                board_arr[i] = line
                print(line)

        self.place_toggle = False
        self.piece_to_move = None

        self.cell_array = [[Tile(self) for _ in range(8)] for _ in range(8)]

        row_color = True

        for i in range(8):
            for j in range(8):
                if j % 2 != 0:
                    self.cell_array[i][j].set_attr(True, i , j) if row_color else self.cell_array[i][j].set_attr(False, i, j)
                    self.cell_array[i][j].configure(text=" " + board_arr[i][j] + " ", fg="red")
                    
                else:
                    self.cell_array[i][j].set_attr(False, i, j) if row_color else self.cell_array[i][j].set_attr(True, i, j)
                    self.cell_array[i][j].configure(text=" " + board_arr[i][j] + " ", fg="red")
            row_color = not row_color

    def __str__(self):
        output = ""
        for i in range(len(self.cell_array)):
            for j in range(len(self.cell_array[0])):
                output += self.cell_array[i][j]["bg"] + " "

            output += "\n"

        return output

    def set_board(self):
        board_arr = [["" for _ in range(8)] for _ in range(8)]
        with open("output.txt") as f:
            for i in range(8):
                line = f.readline()
                print(line)
                line = line.replace("\r\n", "").replace("\x0c", "").replace("test", "")
                line = line.split(" ")[:-1]

                board_arr[i] = line
                #print(line)
        for i in range(8):
            for j in range(8):
                if j % 2 != 0:
                    self.cell_array[i][j].configure(text=" " + board_arr[i][j] + " ", fg="red")
                else:
                    self.cell_array[i][j].configure(text=" " + board_arr[i][j] + " ", fg="red")



if __name__ == '__main__':
    os.chdir(os.path.dirname(os.path.realpath(__file__)))
    #os.system("g++ main.cpp board.cpp piece.cpp player.cpp ai.cpp")
    a = App()
    #a.play()
    a.mainloop(n=0)