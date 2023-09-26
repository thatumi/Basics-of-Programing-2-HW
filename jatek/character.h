/**
    @file    character.h
    @brief   Itt tortenik a jatekos es a kulonbozo szornyek leirasa
**/

#pragma once

#include "map.h"

class character {
	int hp;
	int posX;
	int posY;
	char onMap = 'F'; /* Ez jelenik meg a terkepen a jatekos helyen. */
	bool alive;
	int dmg;
public:
	character() :
		hp(100), posX(0), posY(1), onMap('F'), alive(true), dmg(10) {  }

	character(int ghp, int gposX, int gposY, char gOnMap, int gdmg) :
		hp(ghp), posX(gposX), posY(gposY), onMap(gOnMap), alive(true), dmg(gdmg) {}


	int getHP();
	void setHP(int ghp);
	int getPosX();
	int getPosY();
	void setPosX(int newPosX);
	void setPosY(int newPosY);
	bool getAlive();
	void setAlive(bool isAlive);
	bool canMoveTo(int x, int y, terkep& mapOne);
	int moveCharacter(char input, terkep& mapOne);
	int getDistance(character& c);
	bool isHere(int x, int y);
	char getOnMap();
	int getDMG();
	void damage(character& c) {
		c.damagedBy(this);
	}

	virtual void damagedBy(character* c) {
		hp = hp - c->dmg;
	}
};


class player : public character {
	int mana;

public:
	player() :
		character(800, 4, 5, 'O', 10), mana(100) {}

	player(int ghp, int gposX, int gposY, int gmana, char gOnMap, int gdmg) :
		character(ghp, gposX, gposY, gOnMap, gdmg), mana(gmana) {}

	int getMana();
	void setMana(int gMana);
	virtual void damagedManaBy(character* c) {
		mana = mana - c->getDMG();
	}

};

/**
	@class   archer
	@brief   Ez az egyik szorny. Kulonlegessege, hogy nem csak 1 csempe tavolrol
	tud tamadni.
**/
class archer : public character {
	int attackDistance;
public:
	archer() :
		character(40, 15, 14, 'I', 10), attackDistance(3) {}

	archer(int ghp, int gposX, int gposY, int gAttackDistance, char gOnMap, int gdmg) :
		character(ghp, gposX, gposY, gOnMap, gdmg), attackDistance(gAttackDistance) {}

	void AI(player &p, terkep& mapOne);
};

/**
	@class	manaBat
	@brief	Ez a masik szorny. Kulonlegessege, hogy manat vesz le HP helyett.
**/
class manaBat : public character {
	int manaEat;
public:
	manaBat() :
		character(20, 15, 15, 'B', 10), manaEat(10) {}

	manaBat(int ghp, int gposX, int gposY, int gManaEat, char gOnMap, int gdmg) :
		character(ghp, gposX, gposY, gOnMap, gdmg), manaEat(gManaEat){}

	void AI(player& p, terkep& mapOne);
	void damageMana(player& p) {
		p.damagedManaBy(this);
	}

};
