#include <iostream>
#include "piece.h"

using namespace std;

Piece::Piece() {
	ident = '*';
	moveArr = (std::pair<int, int>*)std::malloc(sizeof moveArr);
	moveArr[0].first = 0;
	moveArr[0].second = 0;
}

std::pair<int, int>* Piece::move() {
	return moveArr;
}

Pawn::Pawn() {
	ident = 'P';
	isInit = true;
	type = 0;
	moveArr = (std::pair<int, int>*)std::malloc(sizeof moveArr);
	moveArr[0].first = 0;
	moveArr[0].second = -1;
}

Pawn::Pawn(bool side) {
	ident = 'P';
	isInit = true;
	type = side;
	int temp;
	if(type) temp = -1;
	else temp = 1;
	moveArr = (std::pair<int, int>*)std::malloc(sizeof moveArr);
	moveArr[0].first = 0;
	moveArr[0].second = temp;
	
}

Rook::Rook() {
	ident = 'R';
	isInit = true;
	type = 0;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::malloc(28*sizeof moveArr);
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = 0;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].second = 0;
		z++;
	}
}

Rook::Rook(bool side) {
	ident = 'R';
	isInit = true;
	type = side;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::malloc(28*sizeof moveArr);
	for(int x = -7; x < 8; x++) {
			if(x == 0) x++;
			moveArr[z].first = 0;
			moveArr[z].second = x;
			z++;
			moveArr[z].first = x;
			moveArr[z].second = 0;
			z++;
		}
}

Knight::Knight() {
	ident = 'N';
	isInit = true;
	type = 0;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::malloc(8*sizeof moveArr);
	for(int y = -1; y < 2; y++) {
		for(int x = -1; x < 2; x++) {
			moveArr[z].first = 2 * x;
			moveArr[z].second = y;
			z++;
			x++;
		}
		y++;
	}
	for(int y = -1; y < 2; y++) {
		for(int x = -1; x < 2; x++) {
			moveArr[z].first = y;
			moveArr[z].second = 2 * x;
			z++;
			x++;
		}
		y++;
	}
}

Knight::Knight(bool side) {
	ident = 'N';
	isInit = true;
	type = side;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::malloc(8*sizeof moveArr);
	for(int y = -1; y < 2; y++) {
		for(int x = -1; x < 2; x++) {
			moveArr[z].first = 2 * x;
			moveArr[z].second = y;
			z++;
			x++;
		}
		y++;
	}
	for(int y = -1; y < 2; y++) {
		for(int x = -1; x < 2; x++) {
			moveArr[z].first = y;
			moveArr[z].second = 2 * x;
			z++;
			x++;
		}
		y++;
	}
}

Bishop::Bishop() {
	ident = 'B';
	isInit = true;
	type = 0;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::malloc(28*sizeof moveArr);
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = x;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].first = -x;
		z++;
	}
}

Bishop::Bishop(bool side) {
	ident = 'B';
	isInit = true;
	type = side;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::malloc(28*sizeof moveArr);
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = x;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].first = -x;
		z++;
	}
}

King::King() {
	ident = 'K';
	isInit = true;
	type = 0;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::malloc(8*sizeof moveArr);
	for(int x = -1; x < 2; x++) {
		for(int y = -1; y < 2; y++) {
			if(x == y && y == 0) y++;
			moveArr[z].first = x;
			moveArr[z].second = y;
			z++;
		}
	}
}

King::King(bool side) {
	ident = 'K';
	isInit = true;
	type = side;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::malloc(8*sizeof moveArr);
	for(int x = -1; x < 2; x++) {
		for(int y = -1; y < 2; y++) {
			if(x == y && y == 0) y++;
			moveArr[z].first = x;
			moveArr[z].second = y;
			z++;
		}
	}
}

Queen::Queen() {
	ident = 'Q';
	isInit = true;
	type = 0;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::malloc(56*sizeof moveArr);
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = x;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].first = -x;
		z++;
	}
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = 0;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].second = 0;
		z++;
	}
}

Queen::Queen(bool side) {
	ident = 'Q';
	isInit = true;
	type = side;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::malloc(56*sizeof moveArr);
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = x;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].first = -x;
		z++;
	}
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = 0;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].second = 0;
		z++;
	}
}