/*********************************************************************
** Program name: Wormhole.cpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Header file for the Wormhole class. This class
** derives from the Space class. Interacting with this class involves
** asking the player if they would like to activate the wormhole. If
** they do, they are randomly placed on a space with no adjacent
** aliens. Function definitions available in the header file.
*********************************************************************/

#include "Space.hpp"
#include "Wormhole.hpp"
#include "Board.hpp"
#include "inputValidation.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void Wormhole::interact(Player* p, Board* b) {
	int activateWormhole;
	bool validInt = false;

	cout << "Would you like to activate the wormhole?\n";
	cout << "1. Yes\n";
	cout << "2. No\n";

	while (validInt == false) {
		getValidInt(activateWormhole);

		if (activateWormhole < 1 || activateWormhole > 2) {
			cout << "Invalid input - please enter 1 or 2\n";
		}

		else {
			validInt = true;
		}
	}

	if (activateWormhole == 1) {
		b->placePlayer(p);
	}
}

void Wormhole::print() {
	if (playerInSpace != nullptr && alienInSpace != nullptr) {
		cout << "!";
	}

	else if (playerInSpace != nullptr) {
		cout << "X";
	}

	else if (alienInSpace != nullptr) {
		cout << "^";
	}

	else {
		cout << "O";
	}
}

char Wormhole::getSpaceType() {
	return 'w';
}