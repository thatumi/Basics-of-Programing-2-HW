
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

    //jatekelemek inicializalasa
    terkep mapOne(10, 10);
    player p(800, 4, 5, 200, 'O', 20);
    manaBat bat(200, 5, 5, 10, 'B', 10);
    archer sterling(400, 5, 4, 3, 'I', 20);
    apple a(3, 1);
    superApple s(2, 1);
    gameEngine ge;

    //Jatekallas valtasok
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
        //Jatek kezdetekor a karakterek betoltese a mapba
        mapOne.setArrayValue(p.getPosX(), p.getPosY(), p.getOnMap());
        mapOne.setArrayValue(bat.getPosX(), bat.getPosY(), bat.getOnMap());
        mapOne.setArrayValue(sterling.getPosX(), sterling.getPosY(), sterling.getOnMap());
        ge.startGame(mapOne, p, bat, sterling, a, s);

    }

    if (ge.getGameState() == gameState::end) {
        std::cout << "Itt a vege" << endl;
        return 0;
    }

}
#endif

