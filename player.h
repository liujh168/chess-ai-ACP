#ifndef PLAYER_H
#define PLAYER_H

#include "ai.h"

class Player {
	private:
		bool isAi; //0 = human, 1 = robot
		Ai ai;
	public:
		Player(Ai ai); //makes a new computer player of AI type ai
		Player(); //makes a new human player
		
		
};

#endif /* PLAYER_H */