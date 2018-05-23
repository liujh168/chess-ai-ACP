#include <iostream>
#include <math.h>
#include <algorithm>
#include "board.h"
#include <stdlib.h>
#include "weight.cpp"
#include <fstream>
#include <typeinfo>
#include <unistd.h>
#define CAPTURE_VALUE 4;
using namespace std;

Board::Board() {
	turnCount = 0;
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
	turnCount = 0;
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

bool Board::movePiece(int x1, int y1, int x2, int y2, bool storeUndo) {
	if (legalMove(x1, y1, x2, y2)) {
		if(storeUndo) {
			undo.first.first = board[x1][y1];
			undo.second.first = board[x2][y2];
			undo.first.second.first = x1;
			undo.first.second.second = y1;
			undo.second.second.first = x2;
			undo.second.second.second = y2;
		}
		if(board[x1][y1].ident == 'R' && board[x2][y2].ident == '*' && !board[x1][y1].hasMoved && (x2 == 3 || x2 == 5) && board[4][y1].ident == 'K' && !board[5][y1].hasMoved && board[x1][y1].type == board[4][y1].type) {
			if((turn && !black.isAi) || (!turn && !white.isAi)) {
				cout << "Would you like to castle? (Y/N)" << endl;
				char ans;
				cin >> ans;
				switch(ans) {
					case 'Y':
						board[5][y1].hasMoved = true;
						board[x2 == 3 ? 2 : 6][y2] = board[4][y1];
						board[4][y1] = Piece();
						break;
					default:
						break;
				}
			}
			else {
				board[5][y1].hasMoved = true;
				board[x2 == 3 ? 2 : 6][y2] = board[4][y1];
				board[4][y1] = Piece();
			}
		}
		board[x2][y2] = board[x1][y1];
		board[x1][y1] = Piece();
		board[x2][y2].hasMoved = true;
		if(board[x2][y2].ident == 'P' && (y2 == 7 || y2 == 0)) promotion(x2, y2);
		return true;
	}
	return false;
}

bool Board::legalMove(int x1, int y1, int x2, int y2) {
	if (x1 > 7 || x1 < 0 || y1 > 7 || y1 < 0 || x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0) { if ((!turn && !white.isAi) || (turn && !black.isAi))if (msg)std::cout << "Out of bounds" << std::endl; return false; }
	if (!(board[x1][y1].isInit)) { if ((!turn && !white.isAi) || (turn && !black.isAi)) if (msg) std::cout << "Target Piece doesn't exist" << std::endl; return false; }
	if (!(board[x1][y1].type == turn)) { if (msg) std::cout << "Target piece is not yours" << std::endl; return false; }
	if (!(board[x2][y2].ident == '*' || board[x2][y2].type != board[x1][y1].type)) { if (msg) std::cout << "Trying to capture your own piece" << std::endl; return false; }
	if (board[x1][y1].ident == 'P') { //Special Pawn movement/attacking 
		Piece p1 = board[x1][y1];
		Piece p2 = board[x2][y2];
		board[x2][y2] = board[x1][y1];
		board[x1][y1] = Piece();
		if (isCheck(turn)) {
			board[x1][y1] = p1;
			board[x2][y2] = p2;
			if (msg) cout << "Moving Piece puts you in check!" << endl;
			return false;
		}
		board[x1][y1] = p1;
		board[x2][y2] = p2;
		if (x1 == x2 && (y1 == 6 || y1 == 1) && board[x2][y2].ident == '*' && abs(y2 - y1) == 2) {
			if (board[x1][y1 + (board[x1][y1].type ? -1 : 1)].ident != '*') return false;
			return true;
		}
		if (abs(x1 - x2) == 1 && abs(y1 - y2) == 1) {
			if (board[x2][y2].ident != '*') return true;
			//en passant
			else if ((undo.first.first.ident == 'P' && abs(undo.first.second.second - undo.second.second.second) == 2 && (undo.first.second.second == 1 || undo.first.second.second == 6)) && (x2 == undo.second.second.first && ((y2 == undo.second.second.second-1 && turn) || (y2 == undo.second.second.second + 1 && !turn)))) {
				board[undo.second.second.first][undo.second.second.second] = Piece();
				return true;
			}
			else return false;
		}
	}
	for (int x = 0; board[x1][y1].moveArr[x].first != 0 || board[x1][y1].moveArr[x].second != 0; x++) {
		if (board[x1][y1].moveArr[x].first + x1 == x2 && board[x1][y1].moveArr[x].second + y1 == y2) {
			bool br = false;
			if (board[x1][y1].ident == 'P' && board[x2][y2].ident != '*') break;
			else if (board[x1][y1].ident == 'R' || ((board[x1][y1].ident == 'Q' && (x1 - x2 == 0 || y1 - y2 == 0)))) {
				if (x1 - x2 == 0) for (int z = min(y1, y2) + 1; z < max(y1, y2); z++) if (board[x1][z].ident != '*') { br = true; break; }
				if (y1 - y2 == 0) for (int z = min(x1, x2) + 1; z < max(x1, x2); z++) if (board[z][y1].ident != '*') { br = true; break; }
			}
			else if ((board[x1][y1].ident == 'B' || (board[x1][y1].ident == 'Q') && (x1 - x2 != 0 || y1 - y2 != 0))) { //Queens and Bishops
				if (x1 > x2) { //Piece Moves Left
					if (y1 > y2) { //Down
						for (int z = 1; z < abs(x1 - x2); z++) {
							if (board[x1 - z][y1 - z].ident != '*') { br = true; break; }
						}
					}
					else if (y1 < y2) { //Up*
						for (int z = 1; z < abs(x1 - x2); z++) {
							if (board[x1 - z][y1 + z].ident != '*') { br = true; break; }
						}
					}
				}
				else if (x1 < x2) { //Piece Moves Right
					if (y1 > y2) { //Down*
						for (int z = 1; z < abs(x1 - x2); z++) {
							if (board[x1 + z][y1 - z].ident != '*') { br = true; break; }
						}
					}
					else if (y1 < y2) { //Up
						for (int z = 1; z < abs(x1 - x2); z++) {
							if (board[x1 + z][y1 + z].ident != '*') { br = true; break; }
						}
					}
				}
			}
			if (br) break;
			Piece p1 = board[x1][y1];
			Piece p2 = board[x2][y2];
			board[x2][y2] = board[x1][y1];
			board[x1][y1] = Piece();
			if (isCheck(board[x2][y2].type)) {
				board[x1][y1] = p1;
				board[x2][y2] = p2;
				if (msg) cout << "Moving Piece puts you in check!" << endl;
				return false;
			}
			board[x1][y1] = p1;
			board[x2][y2] = p2;
			return true;
		}
	}
	if ((!turn && !white.isAi) || (turn && !black.isAi)) if (msg) std::cout << "Illegal move" << endl;
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

void Board::writeBoard() {
	string output;
	for (int x = 0; x < 8; x++) {
		//std::cout << 8 - x << '|';
		for (int y = 0; y < 8; y++) {
			if (board[y][7 - x].ident == '*') { //blank
				output += "   ";
			}
			else { //piece is black
				output += board[y][7 - x].ident;
				output += to_string(board[y][7 - x].type);
				output += " ";
			}
		}
		output += "\n";
	}
	//cout << output << endl;
	ofstream out("output.txt", std::ofstream::out | std::ofstream::trunc);
	out << output;
	out.flush();
	out.rdbuf()->pubsetbuf(0, 0);
	out.close();
}

void Board::readBoard() {
	string* temp = new string[8];
	ifstream out("output.txt");
	int k = 0;
	while (!out.eof() && k < 8) {
		getline(out, temp[k]); // read the next line into the next string
		++k;
	}
	//cout << temp[0] << temp[1];
	out.close();

	char ptr;

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; j++) {
			//cout << typeid(temp[i].at(j*3)).name() << " ";

			ptr = temp[i].at(j * 3);

			if (ptr == 'R') {
				board[j][7 - i] = Rook(temp[i].at(j * 3 + 1) - '0');
			}
			else if (ptr == 'N') {
				board[j][7 - i] = Knight(temp[i].at(j * 3 + 1) - '0');
			}
			else if (ptr == 'B') {
				board[j][7 - i] = Bishop(temp[i].at(j * 3 + 1) - '0');
			}
			else if (ptr == 'Q') {
				board[j][7 - i] = Queen(temp[i].at(j * 3 + 1) - '0');
			}
			else if (ptr == 'K') {
				board[j][7 - i] = King(temp[i].at(j * 3 + 1) - '0');
			}
			else if (ptr == 'P') {
				board[j][7 - i] = Pawn(temp[i].at(j * 3 + 1) - '0');
			}
			else {
				board[j][7 - i] = Piece();
			}
		}
		//cout << endl;
	}
	delete[] temp;
	//printBoard();

}

bool Board::isCheck(bool player) {
	int x1;
	int y1;
	bool h = msg;
	bool found = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].ident == 'K' && board[i][j].type == player) {
				x1 = i;
				y1 = j;
				i = 8;
				j = 8;
				found = true;
			}
		}
	}
	if(!found) return true;
	bool t = turn;
	turn = !player;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			msg = false;
			int a = x1 - i;
			int b = y1 - j;
			bool possible = false;
			if (board[i][j].ident != '*' && board[i][j].type == turn) for(int x = 0; x < board[i][j].lm + (board[i][j].hasSp ? board[i][j].sp-1:0); x++) {
				if(x < board[i][j].lm) { if(a == board[i][j].moveArr[x].first && b == board[i][j].moveArr[x].second) { possible = true; break; } }
				else if(a == board[i][j].spMoveArr[x - board[i][j].lm].first && b == board[i][j].spMoveArr[x - board[i][j].lm].second) {
					possible = true;
					break;
				}
			}
			if(!possible) continue;
			if (legalMove(i, j, x1, y1)) {
				turn = t;
				msg = h;
				return true;
			}
		}
	}
	msg = h;
	turn = t;
	return false;
}

bool Board::isCheckmate(bool player) {
	cout << "Checking for checkmate..." << endl;
	bool h = false;
	bool t = turn;
	turn = player;
	msg = false;
	int x1;
	int y1;
	if (!isCheck(player)) { turn = t; msg = false; return false; }
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (board[x][y].ident != '*' && board[x][y].type == player) for (int z = 0; z < board[x][y].lm + (board[x][y].hasSp ? board[x][y].sp-1:0); z++) {
				//cout << "Checking " << x << ' ' << y  << " move no. " << z << "..." << endl;
				int x2, y2;
				if (z < board[x][y].lm) {
					x2 = x + board[x][y].moveArr[z].first;
					y2 = y + board[x][y].moveArr[z].second;
				}
				else {
					x2 = x + board[x][y].moveArr[z - board[x][y].lm].first;
					y2 = y + board[x][y].moveArr[z - board[x][y].lm].second;
				}
				if(!legalMove(x, y, x2, y2)) continue;
				Piece p1 = board[x][y];
				Piece p2 = board[x2][y2];
				Piece p3 = board[4][y2];
				Piece p4 = board[2][y2];
				Piece p5 = board[6][y2];
				if(movePiece(x, y, x2, y2, false)) {
					if (!isCheck(player)) {
						board[x][y] = p1;
						board[x2][y2] = p2;
						board[4][y2] = p3;
						board[2][y2] = p4;
						board[6][y2] = p5;
						msg = h;
						turn = t;
						return false;
					}
				}
				board[x][y] = p1;
				board[x2][y2] = p2;
				board[4][y2] = p3;
				board[2][y2] = p4;
				board[6][y2] = p5;
			}
		}
	}
	msg = h;
	turn = t;
	return true;
}

void Board::makeMove() {
	cout << "Making move..." << endl;
	int bestx = 0;
	int besty = 0;
	int moveno = 0;
	int bestscore = turn ? -32767:32767;
	std::pair<std::pair<int, int>, int>* moves;
	moves = new std::pair<std::pair<int, int>, int>[100];
	int msize = 0;
	for (int x = 0; x < 8; x++) for (int y = 0; y < 8; y++) if (board[x][y].type == turn && board[x][y].ident != '*') {
		for (int a = 0; a < board[x][y].lm + (board[x][y].hasSp ? board[x][y].sp-1:0); a++) {
			int x2, y2;
			if(a < board[x][y].lm) {
				x2 = board[x][y].moveArr[a].first + x;
				y2 = board[x][y].moveArr[a].second + y;
			}
			else {
				x2 = board[x][y].spMoveArr[a - board[x][y].lm].first + x;
				y2 = board[x][y].spMoveArr[a - board[x][y].lm].second + y;
			}
			if(!legalMove(x, y, x2, y2)) continue;
			//int score = value(board[x2][y2].ident, board[x2][y2].type, x2, y2) + board[x2][y2].weight - value(board[x][y].ident, board[x][y].type, x, y);
			int score = minimax(2, turn, -32767, 32767);
			if (!turn) {
				if (score < bestscore) {
					moves[0].first.first = x;
					moves[0].first.second = y;
					moves[0].second = a;
					msize = 1;
					bestscore = score;
					cout << score << endl;
				}
				else if (score == bestscore) {
					moves[msize].first.first = x;
					moves[msize].first.second = y;
					moves[msize].second = a;
					msize++;
				}
			}
			else {
				if (score > bestscore) {
					moves[0].first.first = x;
					moves[0].first.second = y;
					moves[0].second = a;
					msize = 1;
					bestscore = score;
					cout << score << endl;
				}
				else if (score == bestscore) {
					moves[msize].first.first = x;
					moves[msize].first.second = y;
					moves[msize].second = a;
					msize++;
				}
			}
		}		
	}
	cout << msize << ' ' << bestscore << ' ' << turn;
	int r = rand() % msize;
	bestx = moves[r].first.first;
	besty = moves[r].first.second;
	moveno = moves[r].second;
	delete[] moves;
	int x2, y2;
	if(moveno < board[bestx][besty].lm) {
		x2 = board[bestx][besty].moveArr[moveno].first + bestx;
		y2 = board[bestx][besty].moveArr[moveno].second + besty;
	}
	else {
		x2 = board[bestx][besty].spMoveArr[moveno - board[bestx][besty].lm].first + bestx;
		y2 = board[bestx][besty].spMoveArr[moveno - board[bestx][besty].lm].second + besty;
	}
	movePiece(bestx, besty, x2, y2, true);
	cout << "Move made" << endl;
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

int Board::value(char piece, bool color, int x, int y) {
	if (x > 7)
		return -32767;
	if (x < 0)
		return -32767;
	if (y > 7)
		return -32767;
	if (y < 0)
		return -32767;
	weight p = weight();
	if (!color) {
		switch (piece) {
		case 'P': return p.pawnArr[x][y];
		case 'N': return p.knightArr[x][y];
		case 'K': return p.kingArr[x][y];
		case 'B': return p.bishopArr[x][y];
		case 'R': return p.rookArr[x][y];
		case 'Q': return p.queenArr[x][y];
		}
	}
	switch (piece) {
	case 'P': return p.pawnArr[7 - x][y];
	case 'N': return p.knightArr[7 - x][y];
	case 'K': return p.kingArr[7 - x][y];
	case 'B': return p.bishopArr[7 - x][y];
	case 'R': return p.rookArr[7 - x][y];
	case 'Q': return p.queenArr[7 - x][y];
	}
}

void Board::undoMove() {
	board[undo.first.second.first][undo.first.second.second] = undo.first.first;
	board[undo.second.second.first][undo.second.second.second] = undo.second.first;
}

int Board::minimax(int depth, bool isMax, int alpha, int beta) {
	if(depth == 0) {
		//cout << -evaluateBoard() << ' ';
		return evaluateBoard();
	}
	else {
		int bestscore = isMax ? -32767:32767;
		for (int x = 0; x < 8; x++) for (int y = 0; y < 8; y++) if (board[x][y].type == turn && board[x][y].ident != '*') {
			for (int a = 0; a < board[x][y].lm + (board[x][y].hasSp ? board[x][y].sp-1:0); a++) {
				int x2, y2;
				if(a < board[x][y].lm) {
					x2 = board[x][y].moveArr[a].first + x;
					y2 = board[x][y].moveArr[a].second + y;
				}
				else {
					x2 = board[x][y].spMoveArr[a - board[x][y].lm].first + x;
					y2 = board[x][y].spMoveArr[a - board[x][y].lm].second + y;
				}
				if (!legalMove(x, y, x2, y2)) continue;
				turn = !turn;
				Piece p1 = board[x][y];
				Piece p2 = board[x2][y2];
				Piece p3 = board[4][y2];
				Piece p4 = board[2][y2];
				Piece p5 = board[6][y2];
				movePiece(x, y, x2, y2, false);
				if(p2.ident != 'K') bestscore = isMax ? max(bestscore, minimax(depth-1, !isMax, alpha, beta)):min(bestscore, minimax(depth-1, !isMax, alpha, beta));
				else bestscore = isMax ? max(bestscore, minimax(0, !isMax, alpha, beta)):min(bestscore, minimax(0, !isMax, alpha, beta));
				turn = !turn;
				board[x][y] = p1;
				board[x2][y2] = p2;
				board[4][y2] = p3;
				board[2][y2] = p4;
				board[6][y2] = p5;
				if(isMax) alpha = max(bestscore, alpha);
				else beta = min(bestscore, beta);
				if(beta <= alpha) break;
			}
		}
		return bestscore;
	}
}

int Board::evaluateBoard() {
	bool initTurn = turn;
	int total = 0;
	for(int x = 0; x < 8; x++) for(int y = 0; y < 8; y++) {
		if(board[x][y].ident != '*') total += 2*board[x][y].weight * (board[x][y].type ? 1 : -1);
		else continue;
		turn = board[x][y].type;
		int m = 0;
		for (int a = 0; a < board[x][y].lm + (board[x][y].hasSp ? board[x][y].sp-1:0); a++) {
				int x2, y2;
				if(a < board[x][y].lm) {
					x2 = board[x][y].moveArr[a].first + x;
					y2 = board[x][y].moveArr[a].second + y;
				}
				else {
					x2 = board[x][y].spMoveArr[a - board[x][y].lm].first + x;
					y2 = board[x][y].spMoveArr[a - board[x][y].lm].second + y;
				}
				if (!legalMove(x, y, x2, y2)) continue;
				m++;
		}
		total += m*value(board[x][y].ident, board[x][y].type, x, y)/10 * (board[x][y].type ? 1 : -1);
	}
	turn = initTurn;
	return total;
}
