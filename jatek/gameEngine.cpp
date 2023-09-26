/**

    @file    gameEngine.cpp
    @brief   Itt tortenik az inputkezeles
    @details ~
**/

#include <iostream>

#include "gameEngine.h"



/**
    @brief Menu input kezeles.
    @details Itt lehet uj jatekot inditani, belepni a map editorba, palyat betolteni, vagy kilepni.
    A menu kezeles karakter inputtal tortenik (j - uj jatek, m - map editor, l - map betoltes, k -
    kilepes), ervenyes inputig iteral a funkcio.
    @return gameState jatekallast returnolja
**/
gameState gameEngine::menu() {
    char keyIn;
    std::cout << "Udvozollek kalandor. Mit szeretnel tenni? j = jatek elinditasa, m = map editor, l = map betoltese fajlbol, k = kilepes" << std::endl;
    std::cin >> keyIn;
    while ((keyIn != 'j' && keyIn != 'm' && keyIn != 'k' && keyIn != 'l') && !std::cin) {
        std::cout << "Hibas input. j = jatek elinditasa, m = map editor, l = map betoltese fajlbol, k = kilepes" << std::endl;
        std::cin >> keyIn;
    }
    if (keyIn == 'j') {
        gameStateField = gameState::inGame;
    }
    else if (keyIn == 'm') {
        gameStateField = gameState::mapEditor;
    }
    else if (keyIn == 'k') {
        gameStateField = gameState::inGame;
    }
    else if (keyIn == 'l') {
        gameStateField = gameState::loading;
    }

    return gameStateField;
}

/**
    @brief Itt tortenik a jatekbeli inputkezeles, es ez a jatek "agya".
    @details A felhasznalo itt tud karakter inputokkal mozogni, tamadni, vagy feladni.
    A jatek korokre van osztva, minden korben minden characternek van 1 lepese (tamadas
    vagy mozgas). A terkep minden korben ujrarajzolodik, rajta a szornyekkel, targyakkal,
    falakkal es jatekossal. Kiirasra kerul a jatekos es szornyek manaja, illetve a jatekos
    manaja. Tamadasnal a jatekos mindenkit sebez, aki 1 csempe hatotavolsagon belul van.

    @return gameState jatekallast returnolja.
**/
gameState gameEngine::startGame(terkep& mapOne, player& p, manaBat& b, archer& i, apple& a, superApple& s) {
    char keyIn;
    char keyMove;
    int moveCheck = 0;
    while (gameStateField != gameState::end) {
        std::cout << "Map magyarazat: B = denever, I = Ijasz, E = Eletero, M = Mana, X = Fal, O = Jatekos(te)" << std::endl;
        mapOne.renderMap();
        std::cout << "Eleted: " << p.getHP() << std::endl;
        std::cout << "Manad: " << p.getMana() << std::endl;
        if (b.getAlive()) {
            std::cout << "Denever elete: " << b.getHP() << std::endl;
        }
        if (i.getAlive()) {
            std::cout << "Ijasz elete: " << i.getHP() << std::endl;
        }
        std::cout << "Mit szeretnel tenni kalandor? M = Mozogni, T = Sima tamadas, U = Ulti tamadas (mana szukseges hozza), F = Feladni" << std::endl;
        std::cin >> keyIn;
        while ((keyIn != 'M' && keyIn != 'T' && keyIn != 'U' && keyIn != 'F') || !std::cin) {
            std::cout << "Nem megengedett karakter! M = Mozogni, T = Sima tamadas, U = Ulti tamadas (mana  szukseges hozza), F = Feladni" << std::endl;
            std::cin >> keyIn;
        }
        switch (keyIn) {
        case 'M':

            std::cout << "Merre szeretnel mozogni? (W, A, S, D)" << std::endl;
            std::cin >> keyMove;
            while ((keyMove != 'W' && keyMove != 'A' && keyMove != 'S' && keyMove != 'D') || !std::cin) {
                std::cout << "Nem megengedett karakter. (W, A, S, D)" << std::endl;
                std::cin >> keyMove;
                break;
            }
            moveCheck = p.moveCharacter(keyMove, mapOne);
            while (moveCheck != 1) {
                std::cout << "Ott akadalyba utkoznel. Merre akarsz mozogni?" << std::endl;
                std::cin >> keyMove;
                while ((keyMove != 'W' && keyMove != 'A' && keyMove != 'S' && keyMove != 'D') || !std::cin) {
                    std::cout << "Nem megengedett karakter. (W, A, S, D)" << std::endl;
                    std::cin >> keyMove;
                    break;
                }
                moveCheck = p.moveCharacter(keyMove, mapOne);
            }
            break;
        case 'T':
            if (p.getDistance(b) <= 2) {
                p.damage(b);
            }
            if (p.getDistance(i) <= 2) {
                p.damage(i);
            }

            break;
        case 'U':
            if (p.getMana() > 100) {
                p.damage(i);
                p.damage(b);
                p.setMana(p.getMana() - 100);
            }

            break;
        case 'F':
            gameStateField = gameState::end;
            break;

        }

        //Almak
        if (!a.getUsed()) {
            mapOne.setArrayValue(a.getPosX(), a.getPosY(), 'E');
            if (a.getPosX() == p.getPosX() && a.getPosY() == p.getPosY()) {
                a.eatenBy(&p);
                a.setUsed(true);
            }
        }
        if (!s.getUsed()) {
            mapOne.setArrayValue(s.getPosX(), s.getPosY(), 'M');
            if (s.getPosX() == p.getPosX() && s.getPosY() == p.getPosY()) {
                s.eatenBy(&p);
                s.setUsed(true);
            }
        }


        //Karakterek
        if (p.getHP() > 0 || (i.getAlive()  && b.getAlive())) {
            mapOne.setArrayValue(p.getPosX(), p.getPosY(), p.getOnMap());
            if (b.getAlive()) {
                b.AI(p, mapOne);
            }
            if (i.getAlive()) {
                i.AI(p, mapOne);
            }
            p.setMana(p.getMana() + 10);
            if (p.getHP() <= 0 || (!i.getAlive() && !b.getAlive())) {
                gameStateField = gameState::end;
            }
        }else {
            gameStateField = gameState::end;
        }

    }
    return gameStateField;
}
