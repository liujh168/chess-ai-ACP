#include <iostream>

#include "player.h"

using namespace std;

Player::Player() {
	isAi = false;
}

Player::Player(Ai ai) {
	isAi = true;
	this->ai = ai;
}
