/*********************************************************************
** Program name: Turret.hpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Header file for the Turret class. This class
** derives from the Space class. Interacting with this class involves
** picking a direction and destroying all aliens in that direction 
** (provided ammo is remaining in the turret).
*********************************************************************/

#ifndef TURRET_HPP
#define TURRET_HPP

class Board;

#include "Space.hpp"

class Turret : public Space {
private:
	int ammo;

public:
	/*********************************************************************
	** Default constructor, sets ammo to 5
	*********************************************************************/
	Turret();

	/*********************************************************************
	** If ammo > 0, gets and validates a direction to fire. Deletes all
	** aliens in chosen direction, reduces ammo by 1.
	*********************************************************************/
	void interact(Player* p, Board* b);

	/*********************************************************************
	** Prints the space based on the values shown in the legend.
	*********************************************************************/
	void print();

	/*********************************************************************
	** returns 't' for turret
	*********************************************************************/
	char getSpaceType();
};

#endif