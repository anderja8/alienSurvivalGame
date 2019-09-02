/*********************************************************************
** Program name: Space.hpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Header file for the Space class. This is the base
** class for the three space types that appear on the gameBoard. It
** contains pointers to the North, East, South, and West spaces around
** the space, boolean and char variables for items, and pointers to
** player or alien objects that may occupy the space. Contains virtual
** functions to interact, print, and return the space type. All other
** member functions are getters and setters.
*********************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include "Alien.hpp"
#include "Player.hpp"

class Board;

class Space {
protected:
	Space * north;
	Space * east;
	Space * south;
	Space * west;
	bool hasItem;
	char item;
	Player * playerInSpace;
	Alien * alienInSpace;

public:
	/*********************************************************************
	** Default constructor, sets all pointers to null and hasItem to false.
	*********************************************************************/
	Space();

	/*********************************************************************
	** Setters and getters
	*********************************************************************/
	void setNorth(Space* s);

	Space* getNorth();

	void setEast(Space* s);

	Space* getEast();

	void setSouth(Space* s);

	Space* getSouth();

	void setWest(Space* s);

	Space* getWest();

	void setHasItem(bool b);

	bool getHasItem();

	void setItem(char c);

	char getItem();

	void setPlayerInSpace(Player* p);

	Player* getPlayerInSpace();

	void setAlienInSpace(Alien* a);

	Alien* getAlienInSpace();

	/*********************************************************************
	** Pure virtual function to interact
	*********************************************************************/
	virtual void interact(Player* p, Board* b) = 0;

	/*********************************************************************
	** Pure virtual function to print
	*********************************************************************/
	virtual void print() = 0;
	
	/*********************************************************************
	** Pure virtual function to return the space type
	*********************************************************************/
	virtual char getSpaceType() = 0;

	/*********************************************************************
	** Virtual destructor. Needed to correctly delete derived classes.
	*********************************************************************/
	virtual ~Space();
};

#endif