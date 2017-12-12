#include "Human.h"
#include <stdio.h>

Human::Human(Logic& l, Board& b, Side s):Player(l, b, s) {}

Human::~Human() {
	delete last;
}

Move* Human::checkMove(int i, int j, vector<Move*> options) {
	unsigned int k;
	for (k = 0; k < options.size(); k++)
		if (options[k]->isEqual(i, j))
			return (options[k]);
	return NULL;
}

bool Human::doMove() {
	// free last move
	delete last;
	int i, j;
	unsigned int k;
	cout << sign() << " it's your turn." << endl;
	vector<Move*> options = l.allowedActions(b, s);
	if (options.size() == 0) {
		cout << "You have no possible moves, turn pass" << endl;
		last = NULL;
		return false;
	}
	cout << "Your Possible Moves are :";
	for (k = 0; k < options.size(); k++) {
		if (k > 0)
			cout <<  ", ";
		options[k]->pMove();
    }
	cout << endl;
	Move * choice;
	// a loop for impossible moves value
	do {
		cout << endl << "Please enter your move row col (for example 3 5): ";
		// get a move parameters
		cin >> i >> j;
		// check if the parameter are int type
		if (!cin.fail()) {
			//skip bad input
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			choice = checkMove(i - 1,j - 1, options);
			// check if the move is possible (in the vector)
			if (choice != NULL) {
				b.update(s, choice);
				// free memory - delete all the other moves
				for (k = 0; k < options.size(); k++)
					if (!options[k]->isEqual(choice))
						delete options[k];
				// save the chosen move
				last = choice;
				return true;
			}
			else
				cout << "This isn't a possible move." << endl;
		} else {
			// user didn't input a number
			cout << "Please enter numbers only." << endl;
			cin.clear(); // reset failbit
			//skip bad input
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while(true);
}
