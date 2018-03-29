#include "piece.h"

Piece::Piece() {
	moveArr[0].first = 0;
	moveArr[0].second = 0;
}

std::pair<int, int>* Piece::move() {
	return moveArr;
}

Pawn::Pawn() {
	type = 0;
	moveArr[0].first = 0;
	moveArr[0].second = -1;
}

Pawn::Pawn(bool side) {
	type = side;
	int temp;
	if(type) temp = -1;
	else temp = 1;
	moveArr[0].first = 0;
	moveArr[0].second = temp;
	
}

Rook::Rook() {
	type = 0;
	int z = 0;
	for(int x = 0; x < 8; x++) {
		for(int y = 0; y < 8; y++) {
			moveArr[z].first = x;
			moveArr[z].second = y;
			z++;
		}
	}
}

Rook::Rook(bool side) {
	type = 1;
	int z = 0;
	for(int x = 0; x < 7; x++) {
		for(int y = 0; y < 7; y++) {
			moveArr[z].first = x;
			moveArr[z].second = y;
			z++;
		}
	}
}

Knight::Knight() {
	type = 0;
	int z = 0;
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
	type = side;
	int z = 0;
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
	type = 0;
	int z = 0;
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
	type = side;
	int z = 0;
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
	type = 0;
	int z = 0;
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
	type = side;
	int z = 0;
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
	type = 0;
	int z = 0;
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = x;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].first = -x;
		z++;
	}
	for(int x = 0; x < 7; x++) {
		for(int y = 0; y < 7; y++) {
			moveArr[z].first = x;
			moveArr[z].second = y;
			z++;
		}
	}
}

Queen::Queen(bool side) {
	type = side;
	int z = 0;
	for(int x = -7; x < 8; x++) {
		if(x == 0) x++;
		moveArr[z].first = x;
		moveArr[z].second = x;
		z++;
		moveArr[z].first = x;
		moveArr[z].first = -x;
		z++;
	}
	for(int x = 0; x < 7; x++) {
		for(int y = 0; y < 7; y++) {
			moveArr[z].first = x;
			moveArr[z].second = y;
			z++;
		}
	}
}