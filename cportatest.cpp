#ifdef CPORTA
#include <stdlib.h>  
#include <stdio.h>
#include "memtrace.h"

#include "gtest_lite.h"

#include "items.h"
#include "character.h"
#include "map.h"
#include "gameEngine.h"
int main(int argc, char* argv[]) {
    terkep mapOne(10, 10);
    mapOne.setArrayValue(5, 5, 'x');
    TEST(map, getArrayValue) {
        EXPECT_EQ('x', mapOne.getArrayValue(5, 5)) << "map getArrayValue nem jo";
    } END

        TEST(map, getSizes) {
        EXPECT_EQ(10, mapOne.getSizeX()) << "map getSizeX nem jo";
        EXPECT_EQ(10, mapOne.getSizeY()) << "map getSizeY nem jo";
    } END

        player pou(100, 1, 1, 200, 'W', 20);
    pou.setPosX(2);
    pou.setPosY(3);
    pou.setHP(88);
    pou.setAlive(false);
    pou.setMana(55);
    TEST(Player, getters) {
        EXPECT_EQ(2, pou.getPosX()) << "player posX nem ok";
        EXPECT_EQ(3, pou.getPosY()) << "player posY nem ok";
        EXPECT_EQ(88, pou.getHP()) << "player HP nem ok";
        EXPECT_EQ(55, pou.getMana()) << "player mana nem ok";
        EXPECT_EQ(20, pou.getDMG()) << "player DMG nem ok";
        EXPECT_EQ(false, pou.getAlive()) << "player HP nem ok";
    } END

        manaBat en(40, 2, 4, 30, 'D', 30);
    en.damageMana(pou);
    TEST(manaBatman, damageMana) {
        EXPECT_EQ(25, pou.getMana()) << "manaBat attack nem ok";
    } END

        archer Sterling(100, 2, 5, 3, 'I', 3);
    Sterling.damage(pou);
    TEST(Archer, damage) {
        EXPECT_EQ(85, pou.getHP()) << "archer attack nem ok";
    } END

        TEST(Character, canMoveTo) {
        EXPECT_EQ(true, pou.canMoveTo(2, 2, mapOne)) << "canMoveTo nem ok";
    } END

        pou.moveCharacter('S', mapOne);
    TEST(Character, moveCharacter) {
        EXPECT_EQ(4, pou.getPosY()) << "moveCharacter nem ok";
    } END

        TEST(Character, getDistance) {
        EXPECT_EQ(1, en.getDistance(Sterling)) << "getDistance nem ok";
    } END

        TEST(Character, isHere) {
        EXPECT_EQ(true, en.isHere(2, 4)) << "isHere buzlik";
    } END

        TEST(Character, getOnMap) {
        EXPECT_EQ('I', Sterling.getOnMap()) << "getOnMap nem ok";
    } END

        apple a(3, 3);
    superApple s(4, 4);
    a.setPositions(5, 4);
    s.setUsed(true);
    TEST(Items, getters) {
        EXPECT_EQ(5, a.getPosX()) << "getPos nem ok";
        EXPECT_EQ(4, a.getPosY()) << "getPos nem ok";
        EXPECT_EQ(true, s.getUsed()) << "getUsed nem ok";
    } END

        a.eatenBy(&pou);
    s.eatenBy(&pou);
    TEST(Items, eatenBy) {
        EXPECT_EQ(95, pou.getHP()) << "eatenBy nem ok";
        EXPECT_EQ(125, pou.getMana()) << "eatenBy nem ok";
    } END

        gameEngine ge;
    ge.setGameState(gameState::loading);
    /* TEST(gameEngine, getter) {
         EXPECT_EQ(gameState::loading, ge.getGameState()) << "gamestate get nem ok";
     } END*/
}

#endif