#ifndef PIECE_H
#define PIECE_H
#include <utility>


class Piece {
	public:
		int lm;
		int sp;
		int weight;
		std::pair<int, int>* moveArr;
		std::pair<int, int>* spMoveArr;
		char ident;
		bool type; //0 = white, 1 = black
		bool isInit; //True if the Piece has been initialized as a Pawn, Rook, Knight, Bishop, King, or Queen
		bool hasSp;
		Piece();
		Piece(bool side); //Sets the colour of the piece
		std::pair<int, int>* move(); //returns a pointer to an array of potential moves that a piece can make with each pair telling the computer the x steps and the y steps that a piece could move in
};

class Pawn : public Piece {
	public:
		Pawn();
		Pawn(bool side);
};

class Rook : public Piece {
	public:
		Rook();
		Rook(bool side);
};

class Knight : public Piece {
	public:
		Knight();
		Knight(bool side);
};

class Bishop : public Piece {
	public:
		Bishop();
		Bishop(bool side);
};

class King : public Piece {
	public:
		King();
		King(bool side);
};

class Queen : public Piece {
	public:
		Queen();
		Queen(bool side);
};

#endif /* PIECE_H */