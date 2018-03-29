#include <iostream>
#include "player.h"
#include "board.h"
#include "piece.h"
#include <string.h>

using namespace std;

int main() {
	string input;
	string movedTo;
	Board b = Board();
	int validMove = 0;
	cout << "Please enter the location of the piece to be moved: " << endl;
	cin >> input;
	cout << endl << "Please enter where you would like to move the piece:" << endl;
	//test for if the move was valid
	/* do cin >> movedTo;
	while (validMove = 0;) {
		if () {
			validMove = 1;
		}
		else {
			cout << "Invalid Move. Please Try Again: " << endl;
			cin >> movedTo;
		}
	}
	*/
	cout << "Hello world!" << endl;
	for (int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
		
			cout << "The location of the pieces: "<< ((char) i + 63) + j+1 << endl;
		}
	}

}