/*********************************************************************
** Program name: Alien.cpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Implementation file for the alien class. This class contains
** ints for the row and column of the alien and a boolean variable to
** say whether the alien has moved. Function descriptions are available
** in the header file.
*********************************************************************/

#include "Alien.hpp"
#include "Player.hpp"
#include <cstdlib>

using std::rand;

Alien::Alien(int r, int c) {
	row = r;
	col = c;
	hasMoved = false;
}

void Alien::move(Player &p) {
	if (p.getRow() == row && p.getCol() < col) {
		col -= 1;
	}

	else if (p.getRow() == row && p.getCol() > col) {
		col += 1;
	}

	else if (p.getRow() < row && p.getCol() == col) {
		row -= 1;
	}

	else if (p.getRow() > row && p.getCol() == col) {
		row += 1;
	}

	else if (p.getRow() < row && p.getCol() < col) {
		int moveDirection = rand() % 2;

		if (moveDirection == 0) {
			row -= 1;
		}

		else {
			col -= 1;
		}
	}

	else if (p.getRow() < row && p.getCol() > col) {
		int moveDirection = rand() % 2;

		if (moveDirection == 0) {
			row -= 1;
		}

		else {
			col += 1;
		}
	}

	else if (p.getRow() > row && p.getCol() < col) {
		int moveDirection = rand() % 2;

		if (moveDirection == 0) {
			row += 1;
		}

		else {
			col -= 1;
		}
	}

	else if (p.getRow() > row && p.getCol() > col) {
		int moveDirection = rand() % 2;

		if (moveDirection == 0) {
			row += 1;
		}

		else {
			col += 1;
		}
	}

	hasMoved = true;
}

int Alien::getRow() {
	return row;
}

void Alien::setRow(int r) {
	row = r;
}

int Alien::getCol() {
	return col;
}

void Alien::setCol(int c) {
	col = c;
}

bool Alien::getHasMoved() {
	return hasMoved;
}

void Alien::setHasMoved(bool b) {
	hasMoved = b;
}