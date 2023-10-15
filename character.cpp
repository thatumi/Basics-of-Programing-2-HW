/**
 * @file    character.cpp
 * @brief   This is where the player and various monsters are described
 */


#include "character.h"


bool character::canMoveTo(int x, int y, map& mapOne) const {
    if (x != -1 && y != -1 && x != mapOne.getSizeX() && y != mapOne.getSizeY()) {
        char check = mapOne.getArrayValue(x, y);
        if (check != 'x') {
            return true;
        }
    }
    return false;
}

int character::moveCharacter(char input, map& mapOne) {
    mapOne.setArrayValue(posX, posY, ' ');
    int newPosX = posX;
    int newPosY = posY;
    switch (input) {
    case 'W':
        newPosY -= 1;
        if (canMoveTo(newPosX, newPosY, mapOne)) {
            posY -= 1;
            return 1;
        }
        else {
            return 2;
        }
    case 'A':
        newPosX -= 1;
        if (canMoveTo(newPosX, newPosY, mapOne)) {
            posX -= 1;
            return 1;
        }
        else {
            return 2;
        }
    case 'S':
        newPosY += 1;
        if (canMoveTo(newPosX, newPosY, mapOne)) {
            posY += 1;
            return 1;
        }
        else {
            return 2;
        }
    case 'D':
        newPosX += 1;
        if (canMoveTo(newPosX, newPosY, mapOne)) {
            posX += 1;
            return 1;
        }
        else {
            return 2;
        }
    }
    mapOne.setArrayValue(posX, posY, getOnMap());
    return 2;
}

bool character::isHere(int x, int y) const {
    if (posX == x && posY == y) {
        return true;
    }
    else {
        return false;
    }
}


/**
 * @brief Getter that returns the player's mana points.
 */
int player::getMana() const {
    return mana;
}

/**
 * @brief Setter that sets the player's mana points.
 * @param int gMana - new mana value
 */
void player::setMana(int gMana) {
    mana = gMana;
}

void archer::AI(player& p, map& mapOne) {
    if (getAlive()) {
        if (getDistance(p) <= attackDistance) {
            damage(p);
            std::cout << "The archer attacked you!" << std::endl;
        }
        else if (p.getPosX() > this->getPosX() && canMoveTo((p.getPosX() + 1), this->getPosY(), mapOne)) {
            moveCharacter('D', mapOne);
        }
        else if (p.getPosX() < this->getPosX() && canMoveTo((p.getPosX() - 1), this->getPosY(), mapOne)) {
            moveCharacter('A', mapOne);
        }
        else if (p.getPosY() > this->getPosY() && canMoveTo(this->getPosX(), (p.getPosX() + 1), mapOne)) {
            moveCharacter('S', mapOne);
        }
        else if (p.getPosX() > this->getPosX() && canMoveTo(this->getPosX(), (p.getPosX() - 1), mapOne)) {
            moveCharacter('W', mapOne);
        }
        mapOne.setArrayValue(this->getPosX(), this->getPosY(), this->getOnMap());
        if (getHP() <= 0) {
            setAlive(false);
        }
    }
}


void manaBat::AI(player& p, map& mapOne) {
    if (getAlive()) {
        if (getDistance(p) <= 1) {
            damageMana(p);
            std::cout << "The mana bat attacked you!" << std::endl;
        }
        else if (p.getPosX() > this->getPosX() && canMoveTo((p.getPosX() + 1), this->getPosY(), mapOne)) {
            moveCharacter('D', mapOne);
        }
        else if (p.getPosX() < this->getPosX() && canMoveTo((p.getPosX() - 1), this->getPosY(), mapOne)) {
            moveCharacter('A', mapOne);
        }
        else if (p.getPosY() > this->getPosY() && canMoveTo(this->getPosX(), (p.getPosX() + 1), mapOne)) {
            moveCharacter('S', mapOne);
        }
        else if (p.getPosX() > this->getPosX() && canMoveTo(this->getPosX(), (p.getPosX() - 1), mapOne)) {
            moveCharacter('W', mapOne);
        }
        mapOne.setArrayValue(this->getPosX(), this->getPosY(), this->getOnMap());

        if (getHP() <= 0) {
            setAlive(false);
        }
    }
}


