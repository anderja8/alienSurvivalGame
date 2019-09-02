/*********************************************************************
** Program name: Turret.cpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Implementation file for the Turret class. This class
** derives from the Space class. Interacting with this class involves
** picking a direction and destroying all aliens in that direction
** (provided ammo is remaining in the turret). Function definitions
** available in header file.
*********************************************************************/

#include "Space.hpp"
#include "Turret.hpp"
#include "Board.hpp"
#include "inputValidation.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

Turret::Turret() {
	ammo = 5;
}

void Turret::interact(Player* p, Board* b) {
	int activateTurret;
	int direction;
	int aliensDestroyed = 0;
	bool validInt = false;
	Space* tempSpace = this;

	if (ammo > 0) {
		cout << "The turret has " << ammo << " ammo left. Would you like to use it?\n";
		cout << "1. Yes\n";
		cout << "2. No\n";

		while (validInt == false) {
			getValidInt(activateTurret);

			if (activateTurret < 1 || activateTurret > 2) {
				cout << "Invalid input - please enter 1 or 2\n";
			}

			else {
				validInt = true;
			}
		}

		validInt = false;

		if (activateTurret == 1) {
			ammo -= 1;

			cout << "Please select a direction to fire\n";
			cout << "1. North\n";
			cout << "2. East\n";
			cout << "3. South\n";
			cout << "4. West\n";

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
				//loop until the edge of the board is reached
				while (tempSpace != nullptr) {
					//delete an alien if it exists
					if (tempSpace->getAlienInSpace() != nullptr) {
						delete tempSpace->getAlienInSpace();
						tempSpace->setAlienInSpace(nullptr);
						aliensDestroyed += 1;
					}
				
					//move north
					tempSpace = tempSpace->getNorth();
				}
			}
			else if (direction == 2) {
				//loop until the edge of the board is reached
				while (tempSpace != nullptr) {
					//delete an alien if it exists
					if (tempSpace->getAlienInSpace() != nullptr) {
						delete tempSpace->getAlienInSpace();
						tempSpace->setAlienInSpace(nullptr);
						aliensDestroyed += 1;
					}

					//move east
					tempSpace = tempSpace->getEast();
				}
			}
			else if (direction == 3) {
				//loop until the edge of the board is reached
				while (tempSpace != nullptr) {
					//delete an alien if it exists
					if (tempSpace->getAlienInSpace() != nullptr) {
						delete tempSpace->getAlienInSpace();
						tempSpace->setAlienInSpace(nullptr);
						aliensDestroyed += 1;
					}

					//move south
					tempSpace = tempSpace->getSouth();
				}
			}
			else if (direction == 4) {
				//loop until the edge of the board is reached
				while (tempSpace != nullptr) {
					//delete an alien if it exists
					if (tempSpace->getAlienInSpace() != nullptr) {
						delete tempSpace->getAlienInSpace();
						tempSpace->setAlienInSpace(nullptr);
						aliensDestroyed += 1;
					}

					//move west
					tempSpace = tempSpace->getWest();
				}
			}

			if (aliensDestroyed == 1) {
				cout << "The laser turret destroyed " << aliensDestroyed << " alien.\n";
			}
			else if (aliensDestroyed > 1) {
				cout << "The laser turret destroyed " << aliensDestroyed << " aliens.\n";
			}
			else {
				cout << "The laser turret missed.\n";
			}
		}
	}

	else {
		cout << "The turret is out of ammo.\n";
	}
}

void Turret::print() {
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
		cout << "T";
	}
}

char Turret::getSpaceType() {
	return 't';
}