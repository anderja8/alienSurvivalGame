/*********************************************************************
** Program name: Board.cpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Implementation file for the board class. This class contains
** integers to hold the number of rows, columns, wormholes, turrets,
** bombs, and ammo on the board. The initial number of aliens is also
** set. Step counters and boolean variables to tell if the player has
** won or lost the game are also available. The board itself is a
** space triple pointer called gameBoard. Function definitions are
** available in the header file.
*********************************************************************/

#include "Board.hpp"
#include "Space.hpp"
#include "Alien.hpp"
#include "Player.hpp"
#include "NormalSpace.hpp"
#include "Wormhole.hpp"
#include "Turret.hpp"
#include "inputValidation.hpp"
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::rand;

Board::Board(Player* p) {
	numRows = 20;
	numCols = 20;
	numWormholes = 10;
	numTurrets = 10;
	numBombs = 15;
	numAmmo = 25;
	numAliens = 7;
	stepsLose = 300;
	stepsWin = 11;
	hasWon = false;
	hasLost = false;


	//initialize all of the spaces
	gameBoard = new Space**[numRows];
	for (int i = 0; i < numRows; i++) {
		gameBoard[i] = new Space*[numCols];
	}

	//set the spaces equal to null
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			gameBoard[i][j] = nullptr;
		}
	}

	//Reassign the spaces appropriately
	for (int i = 0; i < numWormholes; i++) {
		this->placeTurret();
	}

	for (int i = 0; i < numTurrets; i++) {
		this->placeWormhole();
	}

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j] == nullptr) {
				gameBoard[i][j] = new NormalSpace;
			}
		}
	}

	//Set NESW pointers for the spaces
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			//top left corner
			if (i == 0 && j == 0) {
				//gameBoard[i][j]->setNorth(gameBoard[i - 1][j]);
				gameBoard[i][j]->setEast(gameBoard[i][j + 1]);
				gameBoard[i][j]->setSouth(gameBoard[i + 1][j]);
				//gameBoard[i][j]->setWest(gameBoard[i][j - 1]);
			}

			//top right corner
			else if (i == 0 && j == numCols - 1) {
				//gameBoard[i][j]->setNorth(gameBoard[i - 1][j]);
				//gameBoard[i][j]->setEast(gameBoard[i][j + 1]);
				gameBoard[i][j]->setSouth(gameBoard[i + 1][j]);
				gameBoard[i][j]->setWest(gameBoard[i][j - 1]);
			}

			//top border
			else if (i == 0) {
				//gameBoard[i][j]->setNorth(gameBoard[i - 1][j]);
				gameBoard[i][j]->setEast(gameBoard[i][j + 1]);
				gameBoard[i][j]->setSouth(gameBoard[i + 1][j]);
				gameBoard[i][j]->setWest(gameBoard[i][j - 1]);
			}

			//bottom left corner
			else if (i == numRows - 1 && j == 0) {
				gameBoard[i][j]->setNorth(gameBoard[i - 1][j]);
				gameBoard[i][j]->setEast(gameBoard[i][j + 1]);
				//gameBoard[i][j]->setSouth(gameBoard[i + 1][j]);
				//gameBoard[i][j]->setWest(gameBoard[i][j - 1]);
			}

			//bottom right corner
			else if (i == numRows - 1 && j == numCols - 1) {
				gameBoard[i][j]->setNorth(gameBoard[i - 1][j]);
				//gameBoard[i][j]->setEast(gameBoard[i][j + 1]);
				//gameBoard[i][j]->setSouth(gameBoard[i + 1][j]);
				gameBoard[i][j]->setWest(gameBoard[i][j - 1]);
			}

			//bottom border
			else if (i == numRows - 1) {
				gameBoard[i][j]->setNorth(gameBoard[i - 1][j]);
				gameBoard[i][j]->setEast(gameBoard[i][j + 1]);
				//gameBoard[i][j]->setSouth(gameBoard[i + 1][j]);
				gameBoard[i][j]->setWest(gameBoard[i][j - 1]);
			}

			//left border
			else if (j == 0) {
				gameBoard[i][j]->setNorth(gameBoard[i - 1][j]);
				gameBoard[i][j]->setEast(gameBoard[i][j + 1]);
				gameBoard[i][j]->setSouth(gameBoard[i + 1][j]);
				//gameBoard[i][j]->setWest(gameBoard[i][j - 1]);
			}

			//right border
			else if (j == numCols - 1) {
				gameBoard[i][j]->setNorth(gameBoard[i - 1][j]);
				//gameBoard[i][j]->setEast(gameBoard[i][j + 1]);
				gameBoard[i][j]->setSouth(gameBoard[i + 1][j]);
				gameBoard[i][j]->setWest(gameBoard[i][j - 1]);
			}

			//all interior spaces
			else {
				gameBoard[i][j]->setNorth(gameBoard[i - 1][j]);
				gameBoard[i][j]->setEast(gameBoard[i][j + 1]);
				gameBoard[i][j]->setSouth(gameBoard[i + 1][j]);
				gameBoard[i][j]->setWest(gameBoard[i][j - 1]);
			}
		}
	}

	//Distribute items
	for (int i = 0; i < numBombs; i++) {
		this->placeBombs();
	}

	for (int i = 0; i < numAmmo; i++) {
		this->placeAmmo();
	}

	this->placeRadio();

	//place aliens
	for (int i = 0; i < numAliens; i++) {
		this->placeAlien();
	}

	//place player
	this->placePlayer(p);
}

//Board::Board(Player p, int rows, int cols, int wormholes, int turrets, int bombs, int ammo, int aliens) { }

void Board::placeWormhole() {
	int eligibleSpaces = 0;
	int chosenSpace;
	int tempSpace = 0;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j] == nullptr) {
				eligibleSpaces += 1;
			}
		}
	}

	if (eligibleSpaces > 0) {
		chosenSpace = rand() % eligibleSpaces + 1;

		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				if (gameBoard[i][j] == nullptr) {
					tempSpace += 1;

					if (tempSpace == chosenSpace) {
						gameBoard[i][j] = new Wormhole;
					}
				}
			}
		}
	}
}

void Board::placeTurret() {
	int eligibleSpaces = 0;
	int chosenSpace;
	int tempSpace = 0;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j] == nullptr) {
				eligibleSpaces += 1;
			}
		}
	}

	if (eligibleSpaces > 0) {
		chosenSpace = rand() % eligibleSpaces + 1;

		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				if (gameBoard[i][j] == nullptr) {
					tempSpace += 1;

					if (tempSpace == chosenSpace) {
						gameBoard[i][j] = new Turret;
					}
				}
			}
		}
	}
}

void Board::placeBombs() {
	int eligibleSpaces = 0;
	int chosenSpace;
	int tempSpace = 0;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j]->getSpaceType() == 'n' && gameBoard[i][j]->getHasItem() == false) {
				eligibleSpaces += 1;
			}
		}
	}

	if (eligibleSpaces > 0) {
		chosenSpace = rand() % eligibleSpaces + 1;

		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				if (gameBoard[i][j]->getSpaceType() == 'n' && gameBoard[i][j]->getHasItem() == false) {
					tempSpace += 1;

					if (tempSpace == chosenSpace) {
						gameBoard[i][j]->setHasItem(true);
						gameBoard[i][j]->setItem('b');
					}
				}
			}
		}
	}
}

void Board::useBomb(int r, int c) {
	int aliensDestroyed = 0;

	for (int i = (r - 3); i < (r + 4); i++) {
		for (int j = (c - 3); j < (c + 4); j++) {
			if (i > -1 && i < numRows && j > -1 && j < numCols) {
				if (gameBoard[i][j]->getAlienInSpace() != nullptr) {
					delete gameBoard[i][j]->getAlienInSpace();
					gameBoard[i][j]->setAlienInSpace(nullptr);
					aliensDestroyed += 1;
				}
			}
		}
	}

	if (aliensDestroyed == 1) {
		cout << "The bomb destroyed " << aliensDestroyed << " alien.\n";
	}
	else if (aliensDestroyed > 1) {
		cout << "The bomb destroyed " << aliensDestroyed << " aliens.\n";
	}
	else {
		cout << "The bomb missed.\n";
	}
}

void Board::placeAmmo() {
	int eligibleSpaces = 0;
	int chosenSpace;
	int tempSpace = 0;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j]->getSpaceType() == 'n' && gameBoard[i][j]->getHasItem() == false) {
				eligibleSpaces += 1;
			}
		}
	}

	if (eligibleSpaces > 0) {
		chosenSpace = rand() % eligibleSpaces + 1;

		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				if (gameBoard[i][j]->getSpaceType() == 'n' && gameBoard[i][j]->getHasItem() == false) {
					tempSpace += 1;

					if (tempSpace == chosenSpace) {
						gameBoard[i][j]->setHasItem(true);
						gameBoard[i][j]->setItem('a');
					}
				}
			}
		}
	}
}

void Board::placeRadio() {
	int eligibleSpaces = 0;
	int chosenSpace;
	int tempSpace = 0;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j]->getSpaceType() == 'n' && gameBoard[i][j]->getHasItem() == false) {
				eligibleSpaces += 1;
			}
		}
	}

	if (eligibleSpaces > 0) {
		chosenSpace = rand() % eligibleSpaces + 1;

		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				if (gameBoard[i][j]->getSpaceType() == 'n' && gameBoard[i][j]->getHasItem() == false) {
					tempSpace += 1;

					if (tempSpace == chosenSpace) {
						gameBoard[i][j]->setHasItem(true);
						gameBoard[i][j]->setItem('r');
					}
				}
			}
		}
	}
}

void Board::placeAlien() {
	int eligibleSpaces = 0;
	int chosenSpace;
	int tempSpace = 0;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j]->getAlienInSpace() == nullptr && gameBoard[i][j]->getPlayerInSpace() == nullptr) {
				eligibleSpaces += 1;
			}
		}
	}

	if (eligibleSpaces > 0) {
		chosenSpace = rand() % eligibleSpaces + 1;

		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				if (gameBoard[i][j]->getAlienInSpace() == nullptr && gameBoard[i][j]->getPlayerInSpace() == nullptr) {
					tempSpace += 1;

					if (tempSpace == chosenSpace) {
						Alien* tempAlien = new Alien(i, j);
						gameBoard[i][j]->setAlienInSpace(tempAlien);
					}
				}
			}
		}
	}
}

void Board::moveAliens(Player* p) {
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j]->getAlienInSpace() != nullptr && gameBoard[i][j]->getAlienInSpace()->getHasMoved() == false) {
				//Create a temp alien variable, move it
				bool alreadyOccupied = false;
				Alien* tempAlien = gameBoard[i][j]->getAlienInSpace();
				tempAlien->move(*p);
				int tempRow = tempAlien->getRow();
				int tempCol = tempAlien->getCol();

				//test to see whether it moved into another alien
				if (gameBoard[tempRow][tempCol]->getAlienInSpace() != nullptr) {
					alreadyOccupied = true;
				}

				//If it didn't, move the tempAlien to the new space, set old space alien pointer to null
				if (alreadyOccupied == false) {
					gameBoard[tempRow][tempCol]->setAlienInSpace(tempAlien);
					gameBoard[i][j]->setAlienInSpace(nullptr);
				}

				//If it did, reset row and col (alien doesn't move)
				else {
					tempAlien->setRow(i);
					tempAlien->setCol(j);
				}
			}
		}
	}

	//reset hasMoved after looping through the whole board
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j]->getAlienInSpace() != nullptr) {
				gameBoard[i][j]->getAlienInSpace()->setHasMoved(false);
			}
		}
	}
}

void Board::placePlayer(Player* p) {
	int eligibleSpaces = 0;
	int chosenSpace;
	int tempSpace = 0;

	//loop through the interior spaces, find one that is not on or adjacent to an alien
	for (int i = 1; i < numRows - 1; i++) {
		for (int j = 1; j < numCols - 1; j++) {
			if (gameBoard[i][j]->getAlienInSpace() == nullptr && gameBoard[i][j]->getNorth()->getAlienInSpace() == nullptr && gameBoard[i][j]->getEast()->getAlienInSpace() == nullptr
				&& gameBoard[i][j]->getSouth()->getAlienInSpace() == nullptr && gameBoard[i][j]->getWest()->getAlienInSpace() == nullptr) {
				eligibleSpaces += 1;
			}
		}
	}

	if (eligibleSpaces > 0) {
		chosenSpace = rand() % eligibleSpaces + 1;

		for (int i = 1; i < numRows - 1; i++) {
			for (int j = 1; j < numCols - 1; j++) {
				if (gameBoard[i][j]->getAlienInSpace() == nullptr && gameBoard[i][j]->getNorth()->getAlienInSpace() == nullptr && gameBoard[i][j]->getEast()->getAlienInSpace() == nullptr
					&& gameBoard[i][j]->getSouth()->getAlienInSpace() == nullptr && gameBoard[i][j]->getWest()->getAlienInSpace() == nullptr) {
					tempSpace += 1;

					if (tempSpace == chosenSpace) {
						//special case if this is the first time the player is being placed (not from wormhole)
						if (p->getCol() == -1 && p->getRow() == -1) {
							p->setRow(i);
							p->setCol(j);
							gameBoard[i][j]->setPlayerInSpace(p);
						}
						//If player is coming from wormhole, 
						else {
							gameBoard[p->getRow()][p->getCol()]->setPlayerInSpace(nullptr);
							p->setRow(i);
							p->setCol(j);
							gameBoard[i][j]->setPlayerInSpace(p);
						}
					}
				}
			}
		}
	}

	else {
		if (p->getCol() == -1 && p->getRow() == -1) {
			cout << "Error - invalid input conditions. No safe space to place player object to begin game.\n";
		}
		else {
			cout << "Error - wormhole could not find a safe space to place the player. Shutting down wormhole.\n";
		}
	}
}

void Board::movePlayer(Player* p) {
	int direction;
	bool validInt = false;
	int tempRow = p->getRow();
	int tempCol = p->getCol();

	//output menu
	cout << "Pick a direction to move\n";
	cout << "1. North\n";
	cout << "2. East\n";
	cout << "3. South\n";
	cout << "4. West\n";
	cout << "5. Don't move\n";

	//validate input
	while (validInt == false) {
		getValidInt(direction);

		if (direction < 1 && direction > 4) {
			cout << "Invalid input - please enter an integer between 1 and 4\n";
		}
		else if (direction == 1 && tempRow == 0) {
			cout << "Invalid input - you are against the top row and cannot move North. Please enter a different direction\n";
		}
		else if (direction == 2 && tempCol == numCols - 1) {
			cout << "Invalid input - you are against the far right column and cannot move East. Please enter a different direction\n";
		}
		else if (direction == 3 && tempRow == numRows - 1) {
			cout << "Invalid input - you are against the bottom row and cannot move South. Please enter a different direction\n";
		}
		else if (direction == 4 && tempCol == 0) {
			cout << "Invalid input - you are against the far left column and cannot move West. Please enter a different direction\n";
		}
		else {
			validInt = true;
		}
	}

	//change temp row and col based on direction
	if (direction == 1) {
		tempRow = tempRow - 1;
	}
	if (direction == 2) {
		tempCol = tempCol + 1;
	}
	if (direction == 3) {
		tempRow = tempRow + 1;
	}
	if (direction == 4) {
		tempCol = tempCol - 1;
	}

	//set playerpointer in new location to player, set old pointer to null
	if (direction != 5) {
		gameBoard[tempRow][tempCol]->setPlayerInSpace(p);
		gameBoard[p->getRow()][p->getCol()]->setPlayerInSpace(nullptr);
		p->setRow(tempRow);
		p->setCol(tempCol);
	}
}

Space* Board::getPlayerSpace() {

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j]->getPlayerInSpace() != nullptr) {
				return gameBoard[i][j];
			}
		}
	}

	cout << "Error in Board::getPlayerSpace() - could not find space with not null player pointer.\n";
	return nullptr;
}

void Board::reduceStepsLose() {
	stepsLose -= 1;
	if (stepsLose == 0) {
		hasLost = true;
	}
}

int Board::getStepsLose() {
	return stepsLose;
}

void Board::reduceStepsWin() {
	stepsWin -= 1;
	if (stepsWin == 0) {
		hasWon = true;
	}
}

int Board::getStepsWin() {
	return stepsWin;
}

bool Board::getHasWon() {
	return hasWon;
}

bool Board::getHasLost() {
	return hasLost;
}

void Board::interact(int r, int c, Player* p) {
	if (gameBoard[r][c] != nullptr) {
		gameBoard[r][c]->interact(p, this);
	}
}

void Board::printBoard() {
	//print top border
	cout << endl;
	for (int i = 0; i < numRows + 2; i++) {
		cout << "-";
	}
	cout << endl;

	//print edges and interior spaces
	for (int i = 0; i < numRows; i++) {
		cout << "|";
		for (int j = 0; j < numCols; j++) {
			gameBoard[i][j]->print();
			if (gameBoard[i][j]->getAlienInSpace() != nullptr && gameBoard[i][j]->getPlayerInSpace() != nullptr) {
				hasLost = true;
			}
		}
		cout << "|\n";
	}

	//print bottom border
	for (int i = 0; i < numRows + 2; i++) {
		cout << "-";
	}
	cout << endl;
}

Board::~Board() {
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (gameBoard[i][j]->getAlienInSpace() != nullptr) {
				delete gameBoard[i][j]->getAlienInSpace();
			}
			delete gameBoard[i][j];
		}
	}

	for (int i = 0; i < numRows; i++) {
		delete[]gameBoard[i];
	}
	delete[]gameBoard;
}