/*********************************************************************
** Program name: Instructions.cpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Header file for the instructions functions. These
** functions simply print the scenario, instructions, and legend for
** the game. Function definitions are available in the header file.
*********************************************************************/

#include "Instructions.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::getline;

void printIntro() {
	cout << "Welcome to the alien survival game.\n\n";
	cout << "You are a marine stationed at a satellite base orbiting Earth.\n";
	cout << "Your base has been attacked by aliens, and you are the only survivor.\n";
	cout << "You are armed with a ray gun, but have already used all your ammo. However,\n";
	cout << "your fallen comrades have dropped ammo and bombs. Your station is also outfitted\n";
	cout << "with wormholes that randomly change your location, and laser turrets that can \n";
	cout << "destroy all aliens in a certain direction. Your ray gun can only destroy the\n";
	cout << "first alien in a certain direction, while your bombs can destroy all aliens within\n";
	cout << "a three tile radius of you.\n\n";

	cout << "The invasion is still ongoing, with more aliens arriving constantly. However, you\n";
	cout << "can stop the invasion by finding a radio, and alerting the other marines to the invasion.\n";
	cout << "You need to act quickly, as the invasion will completely destroy your base in 300 turns.\n";
	cout << "You must use all of your resources to accomplish this task!\n\n";
}

void printLegend() {
	string dummyString;

	cout << "Legend:\n";
	cout << "X - Player\n";
	cout << "^ - Alien\n";
	cout << "T - Laser Turret\n";
	cout << "O - Wormhole\n";
	cout << ". - Ray Gun Ammo\n";
	cout << "& - Bomb\n";
	cout << "| - Radio\n";
	cout << "! - Alien caught player\n\n";

	cout << "Press enter to begin the game.\n";
	getline(cin, dummyString);
}
