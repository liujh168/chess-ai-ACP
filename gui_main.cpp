#include <iostream>
#include "player.h"
#include "board.h"
#include "piece.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    Board b;
    int command;
    if(argv[1] == "return") command = 0;
    else if (argv[1] == "isLegal") command = 1;
    
    switch(command) {
        case 0:
            b.printBoard();
        case 1:
            cout << b.movePiece(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }
    return 0;
}