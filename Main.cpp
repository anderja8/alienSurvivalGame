/*********************************************************************
** Program name: Main.cpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Main function for the alien survival game. Calls functions
** to initialize the board, play the game, add aliens each turn, and print
** outcomes based on progress made at the time of victory or defeat.
*********************************************************************/

#include "Alien.hpp"
#include "Player.hpp"
#include "Space.hpp"
#include "NormalSpace.hpp"
#include "Wormhole.hpp"
#include "Turret.hpp"
#include "inputValidation.hpp"
#include "Instructions.hpp"
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>

using std::vector;
using std::string;
using std::getline;
using std::cout;
using std::cin;
using std::endl;
using std::rand;
using std::srand;



int main() {
	//seed rand
	srand(time(nullptr));

	Player mainPlayer;
	Board mainBoard(&mainPlayer);
	bool boardChanged;
	string dummyString;

	//Welcome the player to the game
	printIntro();
	printLegend();

	while (mainBoard.getHasLost() != true && mainBoard.getHasWon() != true) {
		//print game status
		if (mainPlayer.getHelpRadioed() == false) {
			cout << mainBoard.getStepsLose() << " turns remain before the alien invasion is complete.\n";
			cout << "Help has not yet been radioed.\n";
		}
		else {
			cout << mainBoard.getStepsLose() << " turns remain before the alien invasion is complete.\n";
			cout << "Help has been radioed and will arrive in " << mainBoard.getStepsWin() << " turns.\n";
		}

		//print the board
		mainBoard.printBoard();

		//continue as long as an alien has not moved into the player
		if (mainBoard.getHasLost() != true) {
			//use items, print the board if a bomb or ray gun was used
			boardChanged = mainPlayer.useItem(mainBoard);
			if (boardChanged == true) {
				mainBoard.printBoard();
			}

			//move the player
			mainBoard.movePlayer(&mainPlayer);

			//if the player didn't move into an alien, interact with the spaces
			if (mainBoard.getHasLost() != true) {
				mainBoard.interact(mainPlayer.getRow(), mainPlayer.getCol(), &mainPlayer);
			}

			//move the aliens
			mainBoard.moveAliens(&mainPlayer);

			//add an alien
			mainBoard.placeAlien();

			//reduce the time limit
			mainBoard.reduceStepsLose();

			//reduce the time until help arrives, if the radio has been activated
			if (mainPlayer.getHelpRadioed() == true) {
				mainBoard.reduceStepsWin();
			}

			//print the final board if the player won on this turn
			if (mainBoard.getHasWon() == true) {
				mainBoard.printBoard();
			}
		}
	}

	if (mainBoard.getHasLost() == true && mainBoard.getHasWon() == true) {
		cout << "Help arrived right as the aliens got to you. While you were not saved, your valiant actions allowed the \n";
		cout << "forces of Earth to respond to the alien threat in time to stop it. Game over.\n";
	}

	else if (mainBoard.getHasLost() == true && mainBoard.getStepsWin() < 10) {
		cout << "Unfortunately, you were defeated before the forces of Earth could get to the aliens. However, your valiant actions\n";
		cout << "to activate the radio and call the forces of Earth allowed them to respond in time to stop the invasion. Game over.\n";
	}

	else if (mainBoard.getHasLost() == true) {
		cout << "Unfortunately, you were defeated before the forces of Earth could get to the aliens. Game over.\n";
	}

	else if (mainBoard.getHasWon() == true) {
		cout << "Help has arrived! Your radio call has saved Earth from the alien invasion. Game over.\n";
	}

	//let the user read the output and choose when to leave
	cout << "Press enter to continue:\n";
	getline(cin, dummyString);

	return 0;
}