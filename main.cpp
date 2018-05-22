#include <iostream>
#include "player.h"
#include "board.h"
#include "piece.h"
#include <string>
#include <unistd.h>
#include <time.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	srand(time(NULL));
	Board b(Player(false), Player(true));
	string input;
	bool playing = true;
	bool checkm8 = false;
	system("CLS");
	b.printBoard();   
	
	while(playing && !checkm8) {
		checkm8 = b.isCheckmate(b.turn);
		if(checkm8) break;
		bool mov = true;
		while(mov) {
			if((!b.turn && !b.white.isAi) || (b.turn && !b.black.isAi)) {
				cout << "Please enter the location of the piece to be moved: ";
				cin >> input;
				if(input.compare("quit") == 0) { playing = false; break; }
				int x1 = input.at(0) - 65;
				int y1 = input.at(1) - 49;
				cout << endl << "Please enter where you would like to move the piece:";
				cin >> input;
				cout << endl;
				if(input.compare("quit") == 0) { playing = false; break; }
				int x2 = input.at(0) - 65;
				int y2 = input.at(1) - 49;
				cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << endl;
				mov = !b.movePiece(x1, y1, x2, y2, true);
				b.promotion(x2, y2);
			}
			else {
				b.makeMove();
				mov = false;
			}
		}
		b.turn = !b.turn;
		sleep(.25);
		system("CLS");
		b.printBoard();
	}
	cout << "Checkmate!" << endl;
	return 0;
}
