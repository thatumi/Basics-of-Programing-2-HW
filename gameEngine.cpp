/**
 * @file    gameEngine.cpp
 * @brief   This is where input handling takes place
 */
#include <iostream>
#include "gameEngine.h"

gameState gameEngine::menu() {
    char keyIn;
    std::cout << "Welcome, adventurer. What would you like to do? j = start game, m = map editor, l = load map from a file, k = exit" << std::endl;
    std::cin >> keyIn;
    while ((keyIn != 'j' && keyIn != 'm' && keyIn != 'k' && keyIn != 'l') || !std::cin) {
        std::cout << "Invalid input. j = start game, m = map editor, l = load map from a file, k = exit" << std::endl;
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

gameState gameEngine::startGame(map& mapOne, player& p, manaBat& b, archer& i, apple& a, superApple& s) {
    char keyIn;
    char keyMove;
    int moveCheck = 0;
    while (gameStateField != gameState::end) {
        std::cout << "Map key: B = bat, I = Archer, E = Health, M = Mana, X = Wall, O = Player(you)" << std::endl;
        mapOne.renderMap();
        std::cout << "Your Health: " << p.getHP() << std::endl;
        std::cout << "Your Mana: " << p.getMana() << std::endl;
        if (b.getAlive()) {
            std::cout << "Bat's Health: " << b.getHP() << std::endl;
        }
        if (i.getAlive()) {
            std::cout << "Archer's Health: " << i.getHP() << std::endl;
        }
        std::cout << "What would you like to do, adventurer? M = Move, T = Attack, U = Ultimate attack (requires mana), F = Surrender" << std::endl;
        std::cin >> keyIn;
        while ((keyIn != 'M' && keyIn != 'T' && keyIn != 'U' && keyIn != 'F') || !std::cin) {
            std::cout << "Invalid input! M = Move, T = Attack, U = Ultimate attack (requires mana), F = Surrender" << std::endl;
            std::cin >> keyIn;
        }
        switch (keyIn) {
        case 'M':
            std::cout << "Where would you like to move? (W, A, S, D)" << std::endl;
            std::cin >> keyMove;
            while ((keyMove != 'W' && keyMove != 'A' && keyMove != 'S' && keyMove != 'D') || !std::cin) {
                std::cout << "Invalid character. (W, A, S, D)" << std::endl;
                std::cin >> keyMove;
                break;
            }
            moveCheck = p.moveCharacter(keyMove, mapOne);
            while (moveCheck != 1) {
                std::cout << "You would hit an obstacle. Where would you like to move?" << std::endl;
                std::cin >> keyMove;
                while ((keyMove != 'W' && keyMove != 'A' && keyMove != 'S' && keyMove != 'D') || !std::cin) {
                    std::cout << "Invalid character. (W, A, S, D)" << std::endl;
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
            if (p.getMana() >= 100) {
                p.damage(i);
                p.damage(b);
                p.setMana(p.getMana() - 100);
            }
            break;
        case 'F':
            gameStateField = gameState::end;
            break;
        }

        // Apples
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

        // Characters
        if (p.getHP() > 0 || (i.getAlive() && b.getAlive())) {
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
        }
        else {
            gameStateField = gameState::end;
        }
    }
    return gameStateField;
}
