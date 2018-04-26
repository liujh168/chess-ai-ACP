	#include <iostream>

#include "player.h"

using namespace std;

Player::Player() {
	isAi = false;
}

Player::Player(bool ai) {
	isAi = ai;
}
