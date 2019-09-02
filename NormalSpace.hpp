/*********************************************************************
** Program name: NormalSpace.hpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Header file for the NormalSpace class. This class
** derives from the Space class. Interacting with this class involves
** picking up an item if the space contains one, or nothing if the
** space does not contain an item.
*********************************************************************/

#ifndef NORMALSPACE_HPP
#define NORMALSPACE_HPP

#include "Space.hpp"
#include "Board.hpp"

class NormalSpace : public Space {
public:
	/*********************************************************************
	** Default constructor, does nothing for this class.
	*********************************************************************/
	NormalSpace();

	/*********************************************************************
	** If hasItem == true, gives the player the option to pick up the item.
	*********************************************************************/
	void interact(Player* p, Board* b);

	/*********************************************************************
	** Prints the space based on the values shown in the legend.
	*********************************************************************/
	void print();

	/*********************************************************************
	** returns 'n' for normal
	*********************************************************************/
	char getSpaceType();
};

#endif