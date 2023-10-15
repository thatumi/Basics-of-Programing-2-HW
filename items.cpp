/**
 * @file    items.cpp
 * @brief   This is where the functions for various items are located
 **/

#include "items.h"
#include "character.h"
#include "map.h"



void apple::setPositions(int newPosX, int newPosY) {
    posX = newPosX;
    posY = newPosY;
}


void apple::eatenBy(player* p) {
    p->setHP(p->getHP() + 10);
}


void superApple::eatenBy(player* p) {
    p->setMana(p->getMana() + 100);
}
