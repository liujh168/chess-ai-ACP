import subprocess, os

def run_cpp(name, param):
    proc = subprocess.Popen(name + param,
                        shell=True)

    so, se = proc.communicate()

    return(str(so))

if __name__ == '__main__':
    os.system("g++ test.cpp")
    print(run_cpp("a ", "1 2 3 4 5"))

'''

UI will use subprocess module to communicate with c++ framework

Each player turn will start with a sanity check
Each move it will pass the following
    turn
    board positions
    piece to be moved
    new location of piece
The framework will return
    whether or not the move is valid
If the position is invalid, it will prompt the user to try again
If it is valid, the UI will record the move and pass
 the board to the framework to begin the AIs turn

For this section, the UI will pass the following
    board positions
It will return
    new board positions

TODO

'''