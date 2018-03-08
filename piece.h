#ifndef PIECE_H
#define PIECE_H
#include <utility>


class Piece {
	public:
		bool type; //0 = white, 1 = black
		Piece();
		Piece(bool side); //Sets the colour of the piece
		std::pair<int, int>* move(); //returns a pointer to an array of potential moves that a piece can make with each pair telling the computer the x steps and the y steps that a piece could move in
};

class Pawn : public Piece {
	public:
		Pawn();
		Pawn(bool side);
		std::pair<int, int>* move();
};

class Rook : public Piece {
	public:
		Rook();
		Rook(bool side);
		std::pair<int, int>* move();
};

class Knight : public Piece {
	public:
		Knight();
		Knight(bool side);
		std::pair<int, int>* move();
};

class Castle : public Piece {
	public:
		Castle();
		Castle(bool side);
		std::pair<int, int>* move();
};

class King : public Piece {
	public:
		King();
		King(bool side);
		std::pair<int, int>* move();
};

class Queen : public Piece {
	public:
		Queen();
		Queen(bool side);
		std::pair<int, int>* move();
};

#endif /* PIECE_H */