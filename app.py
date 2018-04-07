import tkinter as tk

import subprocess

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
            temp = self.master.piece_to_move
            
            self.master.cell_array[temp.row][temp.col] = self
            self.set_attr(temp.color, temp.row, temp.col)
            temp.set_attr(self.color, self.row, self.col)
            
            self.cell_array[self.row][self.col] = temp

            self.piece_to_move = None
        else:
            self.piece_to_move = self


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
                    
                else:
                    self.cell_array[i][j].set_attr(False, i, j) if row_color else self.cell_array[i][j].set_attr(True, i, j)
                    
            row_color = not row_color

    def __str__(self):
        output = ""
        for i in range(len(self.cell_array)):
            for j in range(len(self.cell_array[0])):
                output += self.cell_array[i][j]["bg"] + " "

            output += "\n"

        return output



if __name__ == '__main__':
    a = App()
    #a.play()
    a.mainloop(n=0)