/**
 * @file    character.h
 * @brief   This is where the player and various monsters are described
 */

#pragma once

#include "map.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class character {
    int hp;
    int posX;
    int posY;
    char onMap = 'F'; /* This is displayed on the map at the player's position. */
    bool alive;
    int dmg;

public:
    character() :
        hp(100), posX(0), posY(1), onMap('F'), alive(true), dmg(10) {}

    character(int ghp, int gposX, int gposY, char gOnMap, int gdmg) :
        hp(ghp), posX(gposX), posY(gposY), onMap(gOnMap), alive(true), dmg(gdmg) {}

    /**
     * @brief Getter that returns the character's health points (HP).
     */
    int character::getHP() const{
        return hp;
    }

    /**
     * @brief Setter that sets the character's health points (HP).
     * @param int ghp - new health points value
     */
    void character::setHP(int ghp) {
        hp = ghp;
    }

    /**
     * @brief Getter that returns the character's X position on the map.
     */
    int character::getPosX() const{
        return posX;
    }

    /**
     * @brief Getter that returns the character's Y position on the map.
     */
    int character::getPosY() const{
        return posY;
    }

    /**
     * @brief Setter that sets the character's X position on the map.
     * @param int newPosX - new X position
     */
    void character::setPosX(int newPosX) {
        posX = newPosX;
    }

    /**
     * @brief Setter that sets the character's Y position on the map.
     * @param int newPosY - new Y position
     */
    void character::setPosY(int newPosY) {
        posY = newPosY;
    }

    /**
     * @brief Getter that returns whether the character is still alive.
     */
    bool character::getAlive() const{
        return alive;
    }

    /**
     * @brief Setter that sets the character's "alive" status.
     * @param bool isAlive - new alive status
     */
    void character::setAlive(bool isAlive) {
        alive = isAlive;
    }

    /**
     * @brief This function determines if it's possible to move to a given location.
     * @details The function first checks if the new position is within the map's boundaries.
     * Then it checks if the selected location is not a wall.
     * @param int x - the X position to check
     * @param int y - the Y position to check
     * @param map& mapOne - the map being checked
     */
    bool canMoveTo(int x, int y, map& mapOne) const;

    /**
     * @brief This function moves the character.
     * @details It uses the canMoveTo function to determine if it's possible to move to a given location
     * specified by user input.
     * @param char input - typical W A S D input
     * @param map& mapOne - the map
     * @return 1 if the move was successful, 2 if it was not
     */
    int moveCharacter(char input, map& mapOne);

    /**
     * @brief Calculates the distance between two characters.
     * @param character& c - the character for which the distance is measured
     */
    int character::getDistance(character& c) const{
        return abs(sqrt(pow(posX - c.posX, 2) + pow(posY - c.posY, 2)));
    }

    /**
     * @brief Checks if a character is at a given position.
     * @param int x - the X position to check
     * @param int y - the Y position to check
     */
    bool isHere(int x, int y) const;
    /**
     * @brief Getter that returns the character's representation on the map.
     */
    char character::getOnMap() const{
        return onMap;
    }

    /**
     * @brief Getter that returns the character's damage (damage points).
     */
    int character::getDMG() const{
        return dmg;
    }

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

    int getMana() const;
    void setMana(int gMana);

    virtual void damagedManaBy(character* c) {
        mana = mana - c->getDMG();
    }
};

/**
 * @class   archer
 * @brief   This is one of the monsters. Its specialty is the ability to attack from more than 1 tile away.
 */
class archer : public character {
    int attackDistance;

public:
    archer() :
        character(40, 15, 14, 'I', 10), attackDistance(3) {}

    archer(int ghp, int gposX, int gposY, int gAttackDistance, char gOnMap, int gdmg) :
        character(ghp, gposX, gposY, gOnMap, gdmg), attackDistance(gAttackDistance) {}


    /**
     * @brief Archer's "AI." If the player is within a certain distance, it attacks and decreases HP.
     * If not, it approaches the player. It also updates the position on the map with each step.
     * @param player& p - the player
     * @param map& mapOne - the map
     */
    void AI(player& p, map& mapOne);
};

/**
 * @class   manaBat
 * @brief   This is another monster. Its specialty is that it takes mana instead of HP.
 */
class manaBat : public character {
    int manaEat;

public:
    manaBat() :
        character(20, 15, 15, 'B', 10), manaEat(10) {}

    manaBat(int ghp, int gposX, int gposY, int gManaEat, char gOnMap, int gdmg) :
        character(ghp, gposX, gposY, gOnMap, gdmg), manaEat(gManaEat) {}

    /**
     * @brief Mana bat's "AI." If the player is within a certain distance, it attacks and decreases mana.
     * If not, it approaches the player. It also updates the position on the map with each step.
     * @param player& p - the player
     * @param map& mapOne - the map
     */
    void AI(player& p, map& mapOne);

    void damageMana(player& p) {
        p.damagedManaBy(this);
    }
};
