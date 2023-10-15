/**
 * @file    gameEngine.h
 * @brief   This is where input handling takes place
 */
#pragma once

#include "map.h"
#include "character.h"
#include "items.h"

 /**
  * @enum  gameState
  * @brief Enum for storing the game states.
  */
enum class gameState { inGame, inMenu, mapEditor, end, loading };

class gameEngine {
    gameState gameStateField;

public:
    gameEngine() : gameStateField(gameState::inMenu) {}

    gameState getGameState() {
        return gameStateField;
    };

    void setGameState(gameState input) {
        gameStateField = input;
    };

    /**
     * @brief Handles menu input.
     * @details Here you can start a new game, enter the map editor, load a map from a file, or exit.
     * The menu navigation is done with character input (j - start game, m - map editor, l - load map, k - exit).
     * It iterates until valid input is provided.
     * @return gameState The current game state.
     */
    gameState menu();

    /**
     * @brief Handles in-game input and controls the game flow.
     * @details Here, the player can move with character inputs, attack, or surrender.
     * The game is divided into turns where each character gets one move (either attack or move).
     * The map is redrawn each turn with the player, monsters, items, walls, and other elements.
     * The player's and monsters' health and mana are displayed.
     * The player can choose to move, attack, use an ultimate attack, or surrender.
     * @return gameState The current game state.
     */
    gameState startGame(map& mapOne, player& p, manaBat& b, archer& i, apple& a, superApple& s);

    ~gameEngine() {}
};