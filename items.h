/**
 * @file    items.h
 * @brief   Declarations of various item-related functions are found here
 */

#pragma once

#include "character.h"
#include "map.h"

 /**
  * @class   apple
  * @brief   This class serves as a description of an item that gives health to the player
  */
class apple {
    int posY;
    int posX;
    bool used;

public:
    apple() :
        posY(0), posX(0), used(false) {}

    apple(int gposX, int gposY) :
        posY(gposY), posX(gposX), used(false) {}

    /**
     * @brief Getter for the X position of the apple
     * @return The X position of the apple
     */
    int apple::getPosX() const{
        return posX;
    }

    /**
     * @brief Getter for the Y position of the apple
     * @return The Y position of the apple
     */
    int apple::getPosY() const {
        return posY;
    }

    /**
     * @brief Setter for the X and Y positions of the apple
     * @param newPosX - The new X position
     * @param newPosY - The new Y position
     */
    void setPositions(int newPosX, int newPosY);

    /**
     * @brief Getter for the 'used' attribute of the apple
     * @return The 'used' attribute
     */
    bool apple::getUsed() const {
        return used;
    }

    /**
     * @brief Setter for the 'used' attribute of the apple
     * @param gUsed - The 'used' state to set
     */
    void apple::setUsed(bool gUsed) {
        used = gUsed;
    }

    /**
     * @brief When the player 'eats' the apple, they gain +10 health
     * @param player* p - A pointer to the player
     */
    virtual void eatenBy(player* p);

    virtual ~apple() {}
};

/**
 * @class   superApple
 * @brief   This class serves as a description of an item that gives mana to the player
 */
class superApple : public apple {
public:
    superApple() :
        apple(0, 0) {}

    superApple(int gposX, int gposY) :
        apple(gposX, gposY) {}

    /**
     * @brief When the player 'eats' the super apple, they gain +100 mana
     * @param player* p - A pointer to the player
     */
    void eatenBy(player* p);

    ~superApple() {}
};