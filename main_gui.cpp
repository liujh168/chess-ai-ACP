#include <iostream>
#include "player.h"
#include "board.h"
#include "piece.h"
#include <string>
#include <unistd.h>
#include <fstream>
#include <time.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	srand(time(NULL));
	Board b(Player(false), Player(true));
	b.readBoard();
	//b.printBoard();
	//cout << "test";
	string input;
	bool playing = true;
	bool checkm8 = false;
	//system("CLS");
	b.writeBoard();
	bool mov = true;
	//if((!b.turn && !b.white.isAi) || (b.turn && !b.black.isAi)) {
	std::getline(cin, input);
	cout << endl;
	int x1 = input.at(0) - 65;
	int y1 = input.at(1) - 49;
	std::getline(cin, input);
	cout << endl;
	int x2 = input.at(0) - 65;
	int y2 = input.at(1) - 49;
	mov = b.movePiece(x1, y1, x2, y2, true);
	//b.promotion(x2, y2);
	if(mov){
	b.turn = 1;
	b.makeMove();}
	//system("CLS");
	b.writeBoard();
	return 0;
}