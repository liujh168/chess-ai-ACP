#include <iostream>
#include "player.h"
#include "board.h"
#include "piece.h"
#include <string>

using namespace std;

int main() {
	Board b;
	string input;
	bool playing = true;
	system("CLS");
	b.printBoard();
	while(playing) {
		bool mov = true;
		while(mov) {
			cout << "Please enter the location of the piece to be moved: ";
			cin >> input;
			if(input.compare("quit") == 0) { playing = false; break; }
			int x1 = input.at(0) - 65;
			int y1 = input.at(1) - 49;
			cout << endl << "Please enter where you would like to move the piece:" << endl;
			cin >> input;
			if(input.compare("quit") == 0) { playing = false; break; }
			int x2 = input.at(0) - 65;
			int y2 = input.at(1) - 49;
			cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << endl;
			mov = !b.movePiece(x1, y1, x2, y2);
		}
		b.turn = !b.turn;
		system("CLS");
		b.printBoard();
	}
	return 0;
}