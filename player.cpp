#include <iostream>

#include "player.h"

using namespace std;

void player::Player() {
	isAi = false;
}

void player::Player(Ai ai) {
	isAi = true;
	ai = ai;
}
