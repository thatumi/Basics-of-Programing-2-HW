/**

    @file    character.cpp
    @brief   Itt tortenik a jatekos es a kulonbozo szornyek leirasa
**/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "character.h"





/**
	@brief  Getter ami a character osztaly eleterejet adja vissza
**/
int character::getHP() {
	return hp;
}

/**
	@brief  Setter ami a character osztaly eleterejet allitja
	@param	int ghp - uj eletero
**/
void character::setHP(int ghp) {
	hp = ghp;
}

/**
	@brief  Getter ami a character osztaly x poziciojat adja vissza
**/
int character::getPosX() {
	return posX;
}

/**
	@brief  Getter ami a character osztaly y poziciojat adja vissza
**/
int character::getPosY() {
	return posY;
}

/**
	@brief  Setter ami a character osztaly x poziciojat allitja
	@param	int ghp - uj x pozicio
**/
void character::setPosX(int newPosX) {
	posX = newPosX;
}

/**
	@brief  Setter ami a character osztaly y poziciojat allitja
	@param	int ghp - uj y pozicio
**/
void character::setPosY(int newPosY) {
	posY = newPosY;
}

/**
	@brief  Getter ami azt adja vissza, hogy a character eletben van-e meg
**/
bool character::getAlive() {
	return alive;
}

/**
	@brief  Setter ami a character osztaly "alive" valtozojat allitja
	@param	bool isAlive
**/
void character::setAlive(bool isAlive) {
	alive = isAlive;
}

/**
	@brief  Ez a funkcio allapitja meg, hogy lehet-e a megadott koordinatara
	mozogni.
	@details A funkcio eloszor azt nezi meg, hogy az uj pozicio a map hatarain
	belul van-e. Majd megnezi, hogy a kivalasztott lokacio fal-e.
	@param	int x - x pozicio amit vizsgalunk
	@param	int y - y pozicio amit vizsgalunk
	@param	map& mapOne - a map amin vizsgalunk
**/
bool character::canMoveTo(int x, int y, terkep& mapOne) {
	if (x != -1 && y != -1 && x != mapOne.getSizeX() && y != mapOne.getSizeY()) {
		char check = mapOne.getArrayValue(x, y);
		if (check != 'x') {
			return true;
		}
	}
		return false;
}

/**
	@brief  Ez a funkcio mozgatja a charactert
	@details A canMove funkcio segitsegevel vizsgalja meg, hogy lehet-e egy adott
	helyre mozogni, amit a felhasznalo inputtal ad meg.
	@param	char input - tipikus W A S D
	@param	map& mapOne
	@return 1 ha sikerult mozogni, 2 ha nem
**/
int character::moveCharacter(char input, terkep& mapOne) {
	mapOne.setArrayValue(posX, posY, ' ');
	int newPosX = posX;
	int newPosY = posY;
	switch (input) {
	case 'W':
		newPosY -= 1;
		if (canMoveTo(newPosX, newPosY, mapOne)) {
			posY -= 1;
			return 1;
		} else {
			return 2;
		}
		break;
	case 'A':
		newPosX -= 1;
		if (canMoveTo(newPosX, newPosY, mapOne)) {
			posX -= 1;
			return 1;
		} else {
			return 2;
		}
		break;
	case 'S':
		newPosY += 1;
		if (canMoveTo(newPosX, newPosY, mapOne)) {
			posY += 1;
			return 1;
		} else {
			return 2;
		}
		break;
	case 'D':
		newPosX += 1;
		if (canMoveTo(newPosX, newPosY, mapOne)) {
			posX += 1;
			return 1;
		} else {
			return 2;
		}
		break;
	}
	mapOne.setArrayValue(posX, posY, getOnMap());
	return 2;
}

/**
	@brief  Ket character kozotti tavolsagot szamitja ki
	@param	character& c - a character ami kozott tavolsagot akarunk merni
**/
int character::getDistance(character& c) {
	return abs(sqrt(pow(posX-c.posX, 2) + pow(posY-c.posY, 2)));
}

/**
	@brief  Visszaadja, hogy egy karakter egy adott pozicion van-e
	@param	int x - vizsgalando x ertek
	@param	int y - vizsgalando y ertek
**/
bool character::isHere(int x, int y) {
	if (posX == x && posY == y) {
		return true;
	} else {
		return false;
	}
}
/**
	@brief  Getter, visszaadja, hogy egy character milyen betuvel van jelolve
	a terkepen.
**/
char character::getOnMap() {
	return onMap;
}

/**
	@brief  Getter, visszaadja a player manajat.
**/
int player::getMana() {
	return mana;
}

/**
	@brief  Setter, a player manajat allitja.
	@param	int gMana - az uj mana ertek
**/
void player::setMana(int gMana) {
	mana = gMana;
}

/**
	@brief  Ez az archer "AI"-ja. Ha x csempe tavolsagra van a jatekos, akkor
	kozeledik, egyebkent tamad, ami HP-t vesz le. A terkepen is beallitja minden
	lepesnel a helyet.
	@param	player& p - a jatekos
	@param	map& mapOne - a terkep
**/
void archer::AI(player& p, terkep& mapOne) {
	if (getAlive()) {
		if (getDistance(p) <= attackDistance) {
			damage(p);
			std::cout << "Megtamadott teged az ijasz!" << std::endl;
		} else if (p.getPosX() > this->getPosX() && canMoveTo((p.getPosX() + 1), this->getPosY(), mapOne)) {
			moveCharacter('D', mapOne);
		} else if (p.getPosX() < this->getPosX() && canMoveTo((p.getPosX() - 1), this->getPosY(), mapOne)) {
			moveCharacter('A', mapOne);
		} else if (p.getPosY() > this->getPosY() && canMoveTo(this->getPosX(), (p.getPosX() + 1), mapOne)) {
			moveCharacter('S', mapOne);
		} else if (p.getPosX() > this->getPosX() && canMoveTo(this->getPosX(), (p.getPosX() - 1), mapOne)) {
			moveCharacter('W', mapOne);
		}
		mapOne.setArrayValue(this->getPosX(), this->getPosY(), this->getOnMap());
		if (getHP() <= 0) {
			setAlive(false);
		}
	}
}

/**
	@brief  Ez az bat "AI"-ja. Ha ket csempe tavolsagra van a jatekos, akkor
	kozeledik, egyebkent tamad, ami mana-t vesz le. A terkepen is beallitja
	minden lepesnel a helyet.
	@param	player& p - a jatekos
	@param	map& mapOne - a terkep
**/
void manaBat::AI(player& p, terkep& mapOne) {
	if (getAlive()) {
		if (getDistance(p) <= 1) {
			damageMana(p);
			std::cout << "Megtamadott teged a denever!" << std::endl;
		} else if (p.getPosX() > this->getPosX() && canMoveTo((p.getPosX() + 1), this->getPosY(), mapOne)) {
			moveCharacter('D', mapOne);
		} else if (p.getPosX() < this->getPosX() && canMoveTo((p.getPosX() - 1), this->getPosY(), mapOne)) {
			moveCharacter('A', mapOne);
		} else if (p.getPosY() > this->getPosY() && canMoveTo(this->getPosX(), (p.getPosX() + 1), mapOne)) {
			moveCharacter('S', mapOne);
		} else if (p.getPosX() > this->getPosX() && canMoveTo(this->getPosX(), (p.getPosX() - 1), mapOne)) {
			moveCharacter('W', mapOne);
		}
		mapOne.setArrayValue(this->getPosX(), this->getPosY(), this->getOnMap());

		if (getHP() <= 0) {
			setAlive(false);
		}
	}
}

/**
	@brief  Getter, visszaadja a character tamadoerejet.
**/
int character::getDMG() {
	return dmg;
}


