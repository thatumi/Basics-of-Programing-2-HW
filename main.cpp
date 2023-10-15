
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


#include "items.h"
#include "character.h"
#include "map.h"
#include "gameEngine.h"


using namespace std;


#ifndef CPORTA
int main(int argc, char* argv[]) {

    //init map, player, enemies, items
    map mapOne(10, 10);
    player p(800, 4, 5, 200, 'O', 20);
    manaBat bat(200, 5, 5, 10, 'B', 10);
    archer sterling(400, 5, 4, 3, 'I', 20);
    apple a(3, 1);
    superApple s(2, 1);
    gameEngine ge;

    //gamestate changes
    if (ge.getGameState() == gameState::inMenu) {
        ge.menu();
    } if (ge.getGameState() == gameState::mapEditor) {
        mapOne.setMap();
        mapOne.saveMap();
        ge.setGameState(gameState::inGame);
    } if (ge.getGameState() == gameState::loading) {
        mapOne.loadMap();
        ge.setGameState(gameState::inGame);
    } if (ge.getGameState() == gameState::inGame) {
        //Load characters into the map
        mapOne.setArrayValue(p.getPosX(), p.getPosY(), p.getOnMap());
        mapOne.setArrayValue(bat.getPosX(), bat.getPosY(), bat.getOnMap());
        mapOne.setArrayValue(sterling.getPosX(), sterling.getPosY(), sterling.getOnMap());
        ge.startGame(mapOne, p, bat, sterling, a, s);

    }

    if (ge.getGameState() == gameState::end) {
        std::cout << "The end" << endl;
        return 0;
    }

}
#endif

