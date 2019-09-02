/*********************************************************************
** Program name: Wormhole.hpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Header file for the Wormhole class. This class
** derives from the Space class. Interacting with this class involves
** asking the player if they would like to activate the wormhole. If
** they do, they are randomly placed on a space with no adjacent
** aliens.
*********************************************************************/

#ifndef WORMHOLE_HPP
#define WORMHOLE_HPP

class Board;

#include "Space.hpp"

class Wormhole : public Space {
public:
	/*********************************************************************
	** Gets and validates choice to activate wormhole. Calls placePlayer
	** function if wormhole is activated.
	*********************************************************************/
	void interact(Player* p, Board* b);

	/*********************************************************************
	** Prints the space based on the values shown in the legend.
	*********************************************************************/
	void print();

	/*********************************************************************
	** Returns 'w' for wormhole
	*********************************************************************/
	char getSpaceType();
};

#endif