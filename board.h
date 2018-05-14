#ifndef BOARD_H
#define BOARD_H

#include "player.h"
#include "piece.h"

class Board {
	private:
		Piece board[8][8];
		std::pair<std::pair<Piece, std::pair<int, int> >, std::pair<Piece, std::pair<int, int> > > undo;
		bool msg = false;
	public:
		Player white;
		Player black;
		bool turn; //0 - White, 1 black
		Board(); //Default constructor, white is human and black is AI
		Board(Player white, Player black); //Initialize the Board with two players that are specified to be either AI or human
		bool movePiece(int x1, int y1, int x2, int y2); //Moves a piece from (x1, y1) to (x2, y2); returns true and moves the piece if the move is legal and false otherwise; also handles capturing pieces; this is likely where a bulk of the initial code that runs the game will be
		void printBoard(); //Prints out the current state of the board
		void writeBoard();
		void readBoard();
		bool isCheck(bool player); //tests for checkage
		bool isCheckmate(bool player);
		bool legalMove(int x1, int y1, int x2, int y2);
		void makeMove();
		void promotion(int f, int g);
		int value(char piece, bool colour, int x, int y);
		void undoMove();
		int turnCount;
		int minimax(int depth, bool isMax, int alpha, int beta);
		int evaluateBoard();
};

#endif /* BOARD_H */