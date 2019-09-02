/*********************************************************************
** Program name: Player.hpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Header file for the Player class. Contains integers
** for the row and col location, and max number of items. Also
** has a vector container to hold items and a boolean to determine if
** help has been radioed for. Functions to pick up, discard, and use
** items are available.
*********************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

class Board;

using std::vector;

class Player {
private:
	int row, col, maxItems;
	vector <char> items;
	bool helpRadioed;

public:
	/*********************************************************************
	** Default constructor for player. Initializes row and col to -1 as
	** placeholder values.
	*********************************************************************/
	Player();

	/*********************************************************************
	** Asks the user if they would like to use an item (prints a warning
	** if the player is out of items). Uses the item chosen.
	*********************************************************************/
	bool useItem(Board &b);

	/*********************************************************************
	** Prints what items are available to the player. Gets and validates
	** the player's choice of item.
	*********************************************************************/
	char printPickItems();

	/*********************************************************************
	** Gets and validates input on direction to fire ray gun. Destroys
	** the first alien encountered in the chosen direction (found using
	** the board parameter passed).
	*********************************************************************/
	void useRayGun(Board &b);

	/*********************************************************************
	** Calls the board member function for using bomb. Passes player
	** location.
	*********************************************************************/
	void useBomb(Board &b);

	/*********************************************************************
	** Returns true if the user is holding ammo (has an 'a' in items vector)
	*********************************************************************/
	bool holdingAmmo();

	/*********************************************************************
	** Returns true if the user is holding a bomb (has an 'b' in items vector)
	*********************************************************************/
	bool holdingBomb();

	/*********************************************************************
	** Erases the first 'b' found in the items container
	*********************************************************************/
	void discardBomb();

	/*********************************************************************
	** Erases the first 'a' found in the items container
	*********************************************************************/
	void discardAmmo();

	/*********************************************************************
	** adds the input character to the items vector
	*********************************************************************/
	void addItem(char c);

	/*********************************************************************
	** Getters and setters
	*********************************************************************/
	int getMaxItems();

	void setRow(int r);

	int getRow();

	void setCol(int c);

	int getCol();

	int getNumItems();

	bool getHelpRadioed();
};

#endif