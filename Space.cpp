/*********************************************************************
** Program name: Space.cpp
** Author: Jacob Anderson
** Date: 11/29/18
** Description: Implementation file for the Space class. This is the base
** class for the three space types that appear on the gameBoard. It
** contains pointers to the North, East, South, and West spaces around
** the space, boolean and char variables for items, and pointers to
** player or alien objects that may occupy the space. Contains virtual
** functions to interact, print, and return the space type. All other
** member functions are getters and setters. Function explanations
** available in header file.
*********************************************************************/

#include "Space.hpp"
#include "Player.hpp"
#include "Alien.hpp"

Space::Space() {
	north = nullptr;
	east = nullptr;
	south = nullptr;
	west = nullptr;
	hasItem = false;
	playerInSpace = nullptr;
	alienInSpace = nullptr;
}

void Space::setNorth(Space* s) {
	north = s;
}

Space* Space::getNorth() {
	return north;
}

void Space::setEast(Space* s) {
	east = s;
}

Space* Space::getEast() {
	return east;
}

void Space::setSouth(Space* s) {
	south = s;
}

Space* Space::getSouth() {
	return south;
}

void Space::setWest(Space* s) {
	west = s;
}

Space* Space::getWest() {
	return west;
}

void Space::setHasItem(bool b) {
	hasItem = b;
}

bool Space::getHasItem() {
	return hasItem;
}

void Space::setItem(char c) {
	item = c;
}

char Space::getItem() {
	return item;
}

void Space::setPlayerInSpace(Player* p) {
	playerInSpace = p;
}

Player* Space::getPlayerInSpace() {
	return playerInSpace;
}

void Space::setAlienInSpace(Alien* a) {
	alienInSpace = a;
}

Alien* Space::getAlienInSpace() {
	return alienInSpace;
}

Space::~Space() {}