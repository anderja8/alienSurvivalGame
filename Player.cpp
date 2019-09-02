/*********************************************************************
** Program name: Player.cpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Header file for the Player class. Contains integers
** for the row and col location, and max number of items. Also
** has a vector container to hold items and a boolean to determine if
** help has been radioed for. Functions to pick up, discard, and use
** items are available. Function definitions in header file.
*********************************************************************/

#include "Player.hpp"
#include "inputValidation.hpp"
#include "Board.hpp"
#include "Space.hpp"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;

Player::Player() {
	row = -1;
	col = -1;
	maxItems = 10;
	helpRadioed = false;
}

int Player::getMaxItems() {
	return maxItems;
}

void Player::setRow(int r) {
	row = r;
}

int Player::getRow() {
	return row;
}

void Player::setCol(int c) {
	col = c;
}

int Player::getCol() {
	return col;
}

bool Player::useItem(Board &b) {
	int useItem;
	char itemUsed;
	bool validInt = false;

	if (items.size() == 0) {
		cout << "You are out of items.\n";
		return false;
	}
	else if (items.size() == 1 && items[0] == 'r' && helpRadioed == true) {
		cout << "You are only holding the radio, and have already called for help.\n";
	}
	else {
		cout << "Would you like to use an item?\n";
		cout << "1. Yes\n";
		cout << "2. No\n";

		while (validInt == false) {
			getValidInt(useItem);

			if (useItem < 1 || useItem > 2) {
				cout << "Invalid integer - please enter 1 or 2\n";
			}
			else {
				validInt = true;
			}
		}

		if (useItem == 2) {
			return false;
		}

		else {
			itemUsed = this->printPickItems();

			if (itemUsed == 'r') {
				if (helpRadioed == false) {
					helpRadioed = true;
					cout << "You have radioed for help. Now you must survive until help arrives in 10 turns.\n";
				}
				else {
					cout << "You have already called for help with the radio. Reinforcements are coming as fast as they can!\n";
				}
				return false;
			}

			else if (itemUsed == 'a') {
				this->useRayGun(b);
				return true;
			}
			else if (itemUsed == 'b') {
				this->useBomb(b);
				return true;
			}
		}
	}
	return false;
}

char Player::printPickItems() {
	char itemToUse;
	bool validChar = false;
	int numBombs = 0;
	int numAmmo = 0;
	bool holdingRadio = false;

	for (int i = 0; i < items.size(); i++) {
		if (items[i] == 'a') {
			numAmmo += 1;
		}
		else if (items[i] == 'b') {
			numBombs += 1;
		}
		else if (items[i] == 'r') {
			holdingRadio = true;
		}
	}

	cout << "You have " << numBombs << " bombs left, " << numAmmo << " ray gun ammo left, and are";

	if (holdingRadio == false) {
		cout << " not";
	}

	cout << " holding the radio.\n";

	if (helpRadioed == true) {
		cout << " You have already called for help with the radio.\n";
	}
	else if (holdingRadio == true) {
		cout << "You have not yet called for help with the radio.\n";
	}

	cout << "Please choose which item to use. Enter 'r' to use the radio, 'a' to use the ray gun, 'b' to use a bomb,\n";
	cout << "or 'n' to not use any items.\n";

	while (validChar == false) {
		getValidChar(itemToUse);

		if (itemToUse == 'a' && numAmmo == 0) {
			cout << "Invalid selection - no ray gun ammo remaining\n";
		}
		else if (itemToUse == 'b' && numBombs == 0) {
			cout << "Invalid selection - no bombs remaining\n";
		}
		else if (itemToUse == 'r' && holdingRadio == false) {
			cout << "Invalid selection - you are not holding the radio\n";
		}
		else {
			if (itemToUse == 'a' || itemToUse == 'b' || itemToUse == 'r' || itemToUse == 'n') {
				validChar = true;
			}
			else {
				cout << "Invalid character - please enter 'a', 'b', 'r', or 'n'\n";
			}
		}
	}

	return itemToUse;
}

void Player::useRayGun(Board &b) {
	int direction;
	bool alienDestroyed = false;
	bool validInt = false;
	Space* tempSpace = b.getPlayerSpace();

	//remove 1 ammo
	this->discardAmmo();

	//get direction to fire
	cout << "Please select a direction to fire\n";
	cout << "1. North\n";
	cout << "2. East\n";
	cout << "3. South\n";
	cout << "4. West\n";

	//validate
	while (validInt == false) {
		getValidInt(direction);

		if (direction < 1 || direction > 4) {
			cout << "Invalid input - please enter an integer between 1 and 4\n";
		}

		else {
			validInt = true;
		}
	}

	//delete aliens depending on direction chosen
	if (direction == 1) {
		//loop until the edge of the board is reached, or alien is destroyed
		while (tempSpace != nullptr && alienDestroyed == false) {
			//delete an alien if it exists
			if (tempSpace->getAlienInSpace() != nullptr) {
				delete tempSpace->getAlienInSpace();
				tempSpace->setAlienInSpace(nullptr);
				alienDestroyed = true;
			}

			//move north
			tempSpace = tempSpace->getNorth();
		}
	}
	else if (direction == 2) {
		//loop until the edge of the board is reached
		while (tempSpace != nullptr && alienDestroyed == false) {
			//delete an alien if it exists
			if (tempSpace->getAlienInSpace() != nullptr) {
				delete tempSpace->getAlienInSpace();
				tempSpace->setAlienInSpace(nullptr);
				alienDestroyed = true;
			}

			//move east
			tempSpace = tempSpace->getEast();
		}
	}
	else if (direction == 3) {
		//loop until the edge of the board is reached
		while (tempSpace != nullptr && alienDestroyed == false) {
			//delete an alien if it exists
			if (tempSpace->getAlienInSpace() != nullptr) {
				delete tempSpace->getAlienInSpace();
				tempSpace->setAlienInSpace(nullptr);
				alienDestroyed = true;
			}

			//move south
			tempSpace = tempSpace->getSouth();
		}
	}
	else if (direction == 4) {
		//loop until the edge of the board is reached
		while (tempSpace != nullptr && alienDestroyed == false) {
			//delete an alien if it exists
			if (tempSpace->getAlienInSpace() != nullptr) {
				delete tempSpace->getAlienInSpace();
				tempSpace->setAlienInSpace(nullptr);
				alienDestroyed = true;
			}

			//move west
			tempSpace = tempSpace->getWest();
		}
	}

	if (alienDestroyed == true) {
		cout << "The ray gun destroyed an alien.\n";
	}
	else {
		cout << "The ray gun missed.\n";
	}
}

void Player::useBomb(Board &b) {
	//remove 1 ammo
	this->discardBomb();

	//call a board function to calculate what is destroyed
	b.useBomb(row, col);
}

bool Player::holdingAmmo() {
	bool ammoExists = false;

	if (items.empty() == false) {
		for (int i = 0; i < items.size(); i++) {
			if (items[i] == 'a') {
				ammoExists = true;
			}
		}
	}
	return ammoExists;
}

bool Player::holdingBomb() {
	bool bombExists = false;

	if (items.empty() == false) {
		for (int i = 0; i < items.size(); i++) {
			if (items[i] == 'b') {
				bombExists = true;
			}
		}
	}

	return bombExists;
}

void Player::addItem(char c) {
	items.push_back(c);
	cout << "You are now holding " << items.size() << " items out of a maximum of " << maxItems << " items.\n";
}

void Player::discardBomb() {
	bool itemDiscarded = false;

	for (int i = 0; i < items.size(); i++) {
		if (items[i] == 'b' and itemDiscarded == false) {
			vector<char>::iterator tempIterator = items.begin() + i;
			items.erase(tempIterator);
			itemDiscarded = true;
		}
	}
}

void Player::discardAmmo() {
	bool itemDiscarded = false;

	for (int i = 0; i < items.size(); i++) {
		if (items[i] == 'a' and itemDiscarded == false) {
			vector<char>::iterator tempIterator = items.begin() + i;
			items.erase(tempIterator);
			itemDiscarded = true;
		}
	}
}

int Player::getNumItems(){
	return items.size();
}

bool Player::getHelpRadioed() {
	return helpRadioed;
}