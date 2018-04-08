import tkinter as tk

import subprocess, os, copy

class Tile(tk.Button):
    def __init__(self, master):
        tk.Button.__init__(self, master)

        self.master = master

    def set_attr(self, color, row, col):
        self.configure(bg="black") if color else self.configure(bg="white")
        self.configure(command=self.out, text="   ")

        self.color = color
        self.row = row
        self.col = col

        self.grid(row=row, column=col)

    def out(self):
        self.master.place_toggle = not self.master.place_toggle
        
        if self.master.piece_to_move != None:
            temp = [copy.deepcopy(self.master.piece_to_move['text']), copy.deepcopy(self.master.piece_to_move.row), copy.deepcopy(self.master.piece_to_move.col)]
            
            self.master.piece_to_move['text'] = self['text']
            self.master.piece_to_move.row = self.row
            self.master.piece_to_move.col = self.col

            self['text'] = temp[0]
            self.row = temp[1]
            self.col = temp[2]

            self.master.piece_to_move = None
        else:
            self.master.piece_to_move = self


        print(self.row, ", ", self.col, ", ", self.color)

class App(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)

        self.place_toggle = False
        self.piece_to_move = None

        self.cell_array = [[Tile(self) for _ in range(8)] for _ in range(8)]

        row_color = True

        for i in range(8):
            for j in range(8):
                if j % 2 != 0:
                    self.cell_array[i][j].set_attr(True, i , j) if row_color else self.cell_array[i][j].set_attr(False, i, j)
                    self.cell_array[i][j].configure(text=i*8+j, fg="red")
                    
                else:
                    self.cell_array[i][j].set_attr(False, i, j) if row_color else self.cell_array[i][j].set_attr(True, i, j)
                    self.cell_array[i][j].configure(text=i*8+j, fg="red")
            row_color = not row_color

    def __str__(self):
        output = ""
        for i in range(len(self.cell_array)):
            for j in range(len(self.cell_array[0])):
                output += self.cell_array[i][j]["bg"] + " "

            output += "\n"

        return output

    def set_board(self):
        pass



if __name__ == '__main__':
    #os.chdir(os.path.dirname(os.path.realpath(__file__)))
    #os.system("g++ gui_main.cpp")
    a = App()
    #a.play()
    a.mainloop(n=0)