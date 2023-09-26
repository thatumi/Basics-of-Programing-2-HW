/**
	@file    items.cpp
	@brief   Itt vannak a kulonbozo targyak funkcioi
**/

#pragma once

#include "character.h"
#include "map.h"

/**
    @class   apple
    @brief   Ez az osztaly egy targy leirasara szolgal, ami eleterot ad a jatekosnak
**/
class apple {
	int posY;
	int posX;
	bool used;
public:
	apple() :
		posY(0), posX(0), used(false) {}

	apple(int gposX, int gposY) :
		posY(gposY), posX(gposX), used(false) {}


	int getPosX();
	int getPosY();
	void setPositions(int newPosX, int newPosY);
	bool getUsed();
	void setUsed(bool gUsed);
	/**
		@brief  Ha a jatekos 'megeszi' az almat, +10 eleterot kap
		@param player* p - A jatekosra mutato pointer
	**/
	virtual void eatenBy(player* p) {
		p->setHP(p->getHP() + 10);
	}
	virtual ~apple() {}
};

/**
	@class   superApple
	@brief   Ez az osztaly egy targy leirasara szolgal, ami manat ad a jatekosnak
**/
class superApple : public apple {

public:
	superApple() :
		apple(0,0) {}
	superApple(int gposX, int gposY) :
		apple(gposY, gposY) {}

	/**
		@brief  Ha a jatekos 'megeszi' az almat, +100 manat kap
		@param player* p - A jatekosra mutato pointer
	**/
	void eatenBy(player* p) {
		p->setMana(p->getMana() + 100);
	}
	~superApple() {}
};
