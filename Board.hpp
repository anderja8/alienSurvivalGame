/*********************************************************************
** Program name: Board.hpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Header file for the board class. This class contains
** integers to hold the number of rows, columns, wormholes, turrets,
** bombs, and ammo on the board. The initial number of aliens is also
** set. Step counters and boolean variables to tell if the player has
** won or lost the game are also available. The board itself is a
** space triple pointer called gameBoard.
*********************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Space.hpp"
#include "Player.hpp"

class Board {
private:
	Space*** gameBoard;
	int numRows;
	int numCols;
	int numWormholes;
	int numTurrets;
	int numBombs;
	int numAmmo;
	int numAliens;
	int stepsLose;
	int stepsWin;
	bool hasWon;
	bool hasLost;

public:
	/*********************************************************************
	** Default constructor for the board. Creates a randomized gameboard
	** object, and places a player parameter on that board. The randomized
	** board is based on values for the numbers of turrets, wormholes,
	** bombs, and ammo. Adjusting these values will change the difficulty
	** of the game.
	*********************************************************************/
	Board(Player* p);

	/*********************************************************************
	** Randomly initializes one of the null gameBoard pointers to a
	** wormhole.
	*********************************************************************/
	void placeWormhole();

	/*********************************************************************
	** Randomly initializes one of the null gameBoard pointers to a
	** turret.
	*********************************************************************/
	void placeTurret();

	/*********************************************************************
	** Randomly changes the hasItem and item member variables of one of the
	** gameBoard pointers pointing to a NormalSpace to true and 'b'
	*********************************************************************/
	void placeBombs();

	/*********************************************************************
	** Destroys all aliens in a 7x7 grid centered on the row input r and
	** column input c.
	*********************************************************************/
	void useBomb(int r, int c);

	/*********************************************************************
	** Randomly changes the hasItem and item member variables of one of the
	** gameBoard pointers pointing to a NormalSpace to true and 'a'
	*********************************************************************/
	void placeAmmo();

	/*********************************************************************
	** Randomly changes the hasItem and item member variables one of the
	** gameBoard pointers pointing to a NormalSpace to true and 'r'
	*********************************************************************/
	void placeRadio();

	/*********************************************************************
	** Randomly changes the alienInSpace member variable of one of the
	** gameBoard pointers with null alienInSpace and playerInSpace pointers
	** to a new alien.
	*********************************************************************/
	void placeAlien();

	/*********************************************************************
	** Loops through the gameBoard and calls move on all aliens on the
	** board. Uses hasMoved boolean member variable of alien to verify
	** each alien moves only once. The player object parameter must be
	** passed for each alien move call.
	*********************************************************************/
	void moveAliens(Player* p);

	/*********************************************************************
	** Randomly places the passed player object on a board space with no
	** adjacent aliens. Prints an error message if this is not possible.
	** Used for both gameBoard initialization and wormhole interaction.
	*********************************************************************/
	void placePlayer(Player* p);

	/*********************************************************************
	** Gets and validates a direction to move the player. Changes the 
	** playerInSpace member variable of the space being pointed to the
	** player based on the desired direction.
	*********************************************************************/
	void movePlayer(Player* p);

	/*********************************************************************
	** Reduces stepsLose member variable by 1
	*********************************************************************/
	void reduceStepsLose();

	/*********************************************************************
	** Reduces stepsWin member variable by 1
	*********************************************************************/
	void reduceStepsWin();

	/*********************************************************************
	** Getters
	*********************************************************************/
	Space* getPlayerSpace();

	int getStepsLose();

	int getStepsWin();

	bool getHasWon();

	bool getHasLost();

	/*********************************************************************
	** Calls the interact function of the space the player is situated on
	*********************************************************************/
	void interact(int r, int c, Player* p);

	/*********************************************************************
	** Loops through the board, calling the print function for each space
	** pointed to by the gameBoard.
	*********************************************************************/
	void printBoard();

	/*********************************************************************
	** Board destructor. Deletes all dynamic memory.
	*********************************************************************/
	~Board();
};

#endif