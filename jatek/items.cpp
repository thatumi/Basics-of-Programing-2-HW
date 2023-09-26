/**
    @file    items.cpp
    @brief   Itt vannak a kulonbozo targyak funkcioi
**/


using namespace std;
#include <stdio.h>

#include "items.h"
#include "character.h"


/**
    @brief  Getter ami az apple osztaly x poziciojat adja vissza
**/
int apple::getPosX() {
	return posX;
}

/**
	@brief  Getter ami az apple osztaly y poziciojat adja vissza
**/
int apple::getPosY() {
	return posY;
}

/**
	@brief  Setter ami az apple osztaly x es y poziciojat adja vissza
	@param int newPosX - Az uj x pozicio
	@param int newPosY - Az uj y pozicio
**/
void apple::setPositions(int newPosX, int newPosY) {
	posX = newPosX;
	posY = newPosY;
}

/**
	@brief  Getter ami az apple osztaly 'used' tagjat adja vissza
**/
bool apple::getUsed() {
	return used;
}

/**
	@brief  Setter ami az apple osztaly 'used' tagjat allitja
	@param bool gUsed - Az 'used' allapot
**/
void apple::setUsed(bool gUsed) {
	used = gUsed;

}
