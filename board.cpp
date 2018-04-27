#include <iostream>
#include <math.h>
#include <algorithm>
#include "board.h"
#include <stdlib.h>
#include "weight.cpp"

using namespace std;

Board::Board() {
	turn = false;
	white = Player();
	black = Player();
	board[0][0] = Rook(false);
	board[7][0] = Rook(false);
	board[1][0] = Knight(false);
	board[6][0] = Knight(false);
	board[2][0] = Bishop(false);
	board[5][0] = Bishop(false);
	board[3][0] = Queen(false);
	board[4][0] = King(false);
	for (int x = 0; x < 8; x++) board[x][1] = Pawn(false);
	board[0][7] = Rook(true);
	board[7][7] = Rook(true);
	board[1][7] = Knight(true);
	board[6][7] = Knight(true);
	board[2][7] = Bishop(true);
	board[5][7] = Bishop(true);
	board[3][7] = Queen(true);
	board[4][7] = King(true);
	for (int x = 0; x < 8; x++) board[x][6] = Pawn(true);
}

Board::Board(Player white, Player black) {
	this->white = white;
	this->black = black;
	turn = false;
	board[0][0] = Rook(false);
	board[7][0] = Rook(false);
	board[1][0] = Knight(false);
	board[6][0] = Knight(false);
	board[2][0] = Bishop(false);
	board[5][0] = Bishop(false);
	board[3][0] = Queen(false);
	board[4][0] = King(false);
	for (int x = 0; x < 8; x++) board[x][1] = Pawn(false);
	board[0][7] = Rook(true);
	board[7][7] = Rook(true);
	board[1][7] = Knight(true);
	board[6][7] = Knight(true);
	board[2][7] = Bishop(true);
	board[5][7] = Bishop(true);
	board[3][7] = Queen(true);
	board[4][7] = King(true);
	for (int x = 0; x < 8; x++) board[x][6] = Pawn(true);
}

bool Board::movePiece(int x1, int y1, int x2, int y2) {
	if (legalMove(x1, y1, x2, y2)) {
		board[x2][y2] = board[x1][y1];
		board[x1][y1] = Piece();
		return true;
	}
	return false;
}

bool Board::legalMove(int x1, int y1, int x2, int y2) {
	if (x1 > 7 || x1 < 0 || y1 > 7 || y1 < 0 || x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0) { if ((!turn && !white.isAi) || (turn && !black.isAi))std::cout << "Out of bounds" << std::endl; return false; }
	if (!(board[x1][y1].isInit)) { if ((!turn && !white.isAi) || (turn && !black.isAi)) std::cout << "Target Piece doesn't exist" << std::endl; return false; }
	if (ti) if (!(board[x1][y1].type == turn)) { std::cout << "Target piece is not yours" << std::endl; return false; }
	if (board[x1][y1].ident == 'P') { //Special Pawn movement/attacking 
		if (x1 == x2 && (y1 == 6 || y1 == 1) && board[x2][y2].ident == '*' && abs(y2 - y1) == 2) return true;
		if (abs(x1 - x2) == 1 && abs(y1 - y2) == 1 && board[x2][y2].ident != '*') return true;
	}
	std::pair<int, int>* moves = board[x1][y1].move();
	for (int x = 0; moves[x].first != 0 || moves[x].second != 0; x++) {
		if (moves[x].first + x1 == x2 && moves[x].second + y1 == y2) {
			bool br = false;
			if (!(board[x2][y2].ident == '*' || board[x2][y2].type != board[x1][y1].type)) break;
			else if (board[x1][y1].ident == 'P' && board[x2][y2].ident != '*') break;
			else if (board[x1][y1].ident == 'R' || ((board[x1][y1].ident == 'Q' && (x1 - x2 == 0 || y1 - y2 == 0)))) {
				if (x1 - x2 == 0) for (int z = min(y1, y2) + 1; z < max(y1, y2); z++) if (board[x1][z].ident != '*') { br = true; break; }
				if (y1 - y2 == 0) for (int z = min(x1, x2) + 1; z < max(x1, x2); z++) if (board[z][y1].ident != '*') { br = true; break; }
			}
			else if ((board[x1][y1].ident == 'B' || (board[x1][y1].ident == 'Q') && (x1 - x2 != 0 || y1 - y2 != 0))) { //Queens and Bishops
				if(x1 > x2) { //Piece Moves Left
					if(y1 > y2) { //Down
						for(int z = 1; z < abs(x1-x2); z++) {
							if(board[x1-z][y1-z].ident != '*') { br = true; break; }
						}
					}
					else if(y1 < y2) { //Up
						for(int z = 1; z < abs(x1-x2); z++) {
							if(board[x1-z][y1+z].ident != '*') { br = true; break; }
						}
					}
				}
				else if(x1 < x2) { //Piece Moves Right
					if(y1 > y2) { //Down
						for(int z = 1; z < abs(x1-x2); z++) {
							if(board[x1+z][y1-z].ident != '*') { br = true; break; }
						}
					}
					else if(y1 < y2) { //Up
						for(int z = 1; z < abs(x1-x2); z++) {
							if(board[x1+z][y1+z].ident != '*') { br = true; break; }
						}
					}
				}
			}
			if (br) break;
			return true;
		}
	}
	if ((!turn && !white.isAi) || (turn && !black.isAi)) std::cout << "Illegal move" << endl;
	return false;
}

void Board::printBoard() {
	for (int x = 0; x < 8; x++) {
		std::cout << 8 - x << '|';
		for (int y = 0; y < 8; y++) {
			if (board[y][7 - x].ident == '*') { //blank
				std::cout << "  ";
			}
			else if (board[y][7 - x].type) { //piece is black
				std::cout << "\033[1;31m" << board[y][7 - x].ident << "\033[0m\033[1;37m" << ' ';
			}
			else if (board[y][7 - x].type == false) { //white
				std::cout << "\033[1;33m" << board[y][7 - x].ident << "\033[0m\033[1;37m" << ' ';
			}
		}
		std::cout << endl;
	}
	std::cout << " |A B C D E F G H" << endl;
}


bool Board::isCheck(bool player) {
	int x1;
	int y1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].ident == 'K' && board[i][j].type == player) {
				x1 = i;
				y1 = j;
				i = 8;
				j = 8;
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].type != player) if (legalMove(i, j, x1, y1)) {
				return true;
			}
		}
	}
	return false;
}


bool Board::isCheck(int x1, int y1, bool player) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].type != player) if (legalMove(i, j, x1, y1)) {
				cout << i << " " << j << " " << x1 << " " << y1 << endl;
				return true;
			}
		}
	}
	return false;
}

bool Board::isCheckmate(bool player) {
	ti = false;
	int x1;
	int y1;
	if (!isCheck(player)) { ti = true; return false; }
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].ident == 'K' && board[i][j].type == player) {
				x1 = i;
				y1 = j;
				i = 8;
				j = 8;
			}
		}
	}
	bool pm = false;
	for (int x = -1; x < 2; x++) for (int y = -1; y < 2; y++) {
		if (x == 0 && y == 0) continue;
		if (legalMove(x1, y1, x1 + x, y1 + y)) {
			pm = true;
			if (!isCheck(x1 + x, y1 + y, player)) {
				ti = true;
				return false;
			}
		}
	}
	ti = true;
	return !pm;
}

/*bool Board::makeMove() {
	int x = rand() % 8;
	int y = rand() % 8;

	if(board[x][y].type == turn) {
		if(!board[x][y].hasSp) {
			std::pair<int, int>* legal = board[x][y].moveArr;
			int a = rand() % board[x][y].lm;
			return movePiece(x, y, legal[a].first+x, legal[a].second + y);
		}
		else {
			int a = rand() % (board[x][y].lm + board[x][y].sp);
			if(a >= board[x][y].lm) return movePiece(x, y,  board[x][y].moveArr[a].first+x,  board[x][y].moveArr[a].second + y);
			else return movePiece(x, y,  board[x][y].spMoveArr[a- board[x][y].lm].first+x,  board[x][y].spMoveArr[a -  board[x][y].lm].second + y);
		}
	}

	return false;
}*/
bool Board::makeMove() {
	int bestx = 0;
	int besty = 0;
	bool sp = false;
	int moveno = 0;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			if (board[x][y].type == turn) {
				if (!board[x][y].hasSp) {
					std::pair<int, int>* legal = board[x][y].moveArr;
					int a = rand() % board[x][y].lm;
					return movePiece(x, y, legal[a].first + x, legal[a].second + y);
				}
				else {
					int a = rand() % (board[x][y].lm + board[x][y].sp);
					if (a >= board[x][y].lm) return movePiece(x, y, board[x][y].moveArr[a].first + x, board[x][y].moveArr[a].second + y);
					else return movePiece(x, y, board[x][y].spMoveArr[a - board[x][y].lm].first + x, board[x][y].spMoveArr[a - board[x][y].lm].second + y);
				}
			}
		}
	}
	return false;
}

void Board::promotion(int f, int g) {
	char input;
	if (board[f][g].ident == 'P') {
		if ((board[f][g].type == 0 && g == 7) || (board[f][g].type == 1 && g == 0)) {
			if ((!turn && !white.isAi) || (turn && !black.isAi)) {
				cout << "Please enter type to which the pawn will be promoted: " << endl;
				cin >> input;
				if (input == 'Q') {
					board[f][g] = Queen(board[f][g].type);
				}
				else if (input == 'N') {
					board[f][g] = Knight(board[f][g].type);
				}
			}
			else {
				board[f][g] = Queen(board[f][g].type);
			}
		}
	}
}
int Board::value(char piece, int x, int y) {
	weight p = weight();
	switch (piece) {
	case 'P': return p.pawnArr[x][y];
	case 'N': return p.knightArr[x][y];
	case 'K': return p.kingArr[x][y];
	case 'B': return p.bishopArr[x][y];
	case 'R': return p.rookArr[x][y];
	case 'Q': return p.queenArr[x][y];
	}
}