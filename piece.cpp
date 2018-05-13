#include <iostream>
#include "piece.h"

using namespace std;

Piece::Piece() {
	weight = 0;
	ident = '*';
	moveArr = (std::pair<int, int>*)std::calloc(1, sizeof moveArr);
	moveArr[0].first = 0;
	moveArr[0].second = 0;
	lm = 1;
	hasSp = false;
}

std::pair<int, int>* Piece::move() {
	return moveArr;
}

Pawn::Pawn() {
	weight = 10;
	ident = 'P';
	isInit = true;
	type = 0;
	moveArr = (std::pair<int, int>*)std::calloc(1, sizeof moveArr);
	moveArr[0].first = 0;
	moveArr[0].second = -1;
	spMoveArr = (std::pair<int, int>*)std::calloc(3, sizeof spMoveArr);
	spMoveArr[0].first = -1;
	spMoveArr[0].second = -1;
	spMoveArr[1].first = 1;
	spMoveArr[1].second = -1;
	spMoveArr[2].first = 0;
	spMoveArr[2].second = -2;
	lm = 1;
	sp = 3;
	hasSp = true;
}

Pawn::Pawn(bool side) {
	weight = 10;
	ident = 'P';
	isInit = true;
	type = side;
	int temp;
	if(type) temp = -1;
	else temp = 1;
	moveArr = (std::pair<int, int>*)std::calloc(1, sizeof moveArr);
	moveArr[0].first = 0;
	moveArr[0].second = temp;
	spMoveArr = (std::pair<int, int>*)std::calloc(3, sizeof spMoveArr);
	spMoveArr[0].first = -1;
	spMoveArr[0].second = temp;
	spMoveArr[1].first = 1;
	spMoveArr[1].second = temp;
	spMoveArr[2].first = 0;
	spMoveArr[2].second = temp*2;
	lm = 1;
	sp = 3;
	hasSp = true;
}

Rook::Rook() {
	weight = 50;
	ident = 'R';
	isInit = true;
	type = 0;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::calloc(28, sizeof moveArr);
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = 0;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].second = 0;
		z++;
	}
	lm = 28;
	hasSp = false;
}

Rook::Rook(bool side) {
	weight = 50;
	ident = 'R';
	isInit = true;
	type = side;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::calloc(28, sizeof moveArr);
	for(int x = -7; x < 8; x++) {
			if(x == 0) x++;
			moveArr[z].first = 0;
			moveArr[z].second = x;
			z++;
			moveArr[z].first = x;
			moveArr[z].second = 0;
			z++;
		}
	lm = 28;
	hasSp = false;
}

Knight::Knight() {
	weight = 32;
	ident = 'N';
	isInit = true;
	type = 0;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::calloc(8, sizeof moveArr);
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
	lm = 8;
	hasSp = false;
}

Knight::Knight(bool side) {
	weight = 32;
	ident = 'N';
	isInit = true;
	type = side;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::calloc(8, sizeof moveArr);
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
	lm = 8;
	hasSp = false;
}

Bishop::Bishop() {
	weight = 33;
	ident = 'B';
	isInit = true;
	type = 0;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::calloc(28, sizeof moveArr);
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = x;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].second = -x;
		z++;
	}
	lm = 28;
	hasSp = false;
}

Bishop::Bishop(bool side) {
	weight = 33;
	ident = 'B';
	isInit = true;
	type = side;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::calloc(28, sizeof moveArr);
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = x;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].second = -x;
		z++;
	}
	lm = 28;
	hasSp = false;
}

King::King() {
	weight = 10000;
	ident = 'K';
	isInit = true;
	type = 0;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::calloc(8, sizeof moveArr);
	for(int x = -1; x < 2; x++) {
		for(int y = -1; y < 2; y++) {
			if(x == y && y == 0) y++;
			moveArr[z].first = x;
			moveArr[z].second = y;
			z++;
		}
	}
	lm = 8;
	hasSp = false;
}

King::King(bool side) {
	weight = 10000;
	ident = 'K';
	isInit = true;
	type = side;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::calloc(8, sizeof moveArr);
	for(int x = -1; x < 2; x++) {
		for(int y = -1; y < 2; y++) {
			if(x == y && y == 0) y++;
			moveArr[z].first = x;
			moveArr[z].second = y;
			z++;
		}
	}
	lm = 8;
	hasSp = false;
}

Queen::Queen() {
	weight = 90;
	ident = 'Q';
	isInit = true;
	type = 0;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::calloc(56, sizeof moveArr);
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = x;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].second = -x;
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
	lm = 56;
	hasSp = false;
}

Queen::Queen(bool side) {
	weight = 90;
	ident = 'Q';
	isInit = true;
	type = side;
	int z = 0;
	moveArr = (std::pair<int, int>*)std::calloc(56, sizeof moveArr);
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = x;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].second = -x;
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
	lm = 56;
	hasSp = false;
}