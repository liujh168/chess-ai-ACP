#ifndef PLAYER_H
#define PLAYER_H


class Player {
	private:
		bool isAi; //0 = human, 1 = robot
	public:
		Player(bool ai); //makes a new computer player of AI type ai
		Player(); //makes a new human player
		
		
};

#endif /* PLAYER_H */