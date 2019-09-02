/*********************************************************************
** Program name: Alien.hpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Header file for the alien class. This class contains
** ints for the row and column of the alien and a boolean variable to
** say whether the alien has moved.
*********************************************************************/
#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "Player.hpp"

class Alien {
private:
	int row;
	int col;
	bool hasMoved;
	
public:
	/*********************************************************************
	** Constructor for the alien class. Row and column values are required
	** to initialize the object.
	*********************************************************************/
	Alien(int r, int c);

	/*********************************************************************
	** Takes a player as a parameter and moves the alien one space closer
	** to the player. Randomly chooses to move up or right if the
	** player is both up and right of the alien on the gameboard, etc.
	*********************************************************************/
	void move(Player &p);

	/*********************************************************************
	** Getters and setters for the member variables.
	*********************************************************************/
	int getRow();

	void setRow(int r);

	int getCol();

	void setCol(int c);

	bool getHasMoved();

	void setHasMoved(bool b);
};

#endif