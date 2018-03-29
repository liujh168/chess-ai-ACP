#include <iostream>
#include "player.h"
#include "board.h"
#include "piece.h"
#include <string.h>

using namespace std;

int main() {
	string input;
	Board b = Board();
	cout << "Please enter the location of the piece to be moved: " << endl;
	cin >> input;
	cout << "Hello world!" << endl;
	for (int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
		
			cout << "The location of the pieces: "<< ((char) i + 63) + j+1 << endl;
		}
	}

}