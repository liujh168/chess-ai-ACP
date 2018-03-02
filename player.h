#ifndef PLAYER_H
#define PLAYER_H

#include "ai.h"

class Player {
	private:
		bool isAi;
		Ai ai;
	public:
		void Player(Ai ai);
		void Player();
		
		
}

#endif /* PLAYER_H */