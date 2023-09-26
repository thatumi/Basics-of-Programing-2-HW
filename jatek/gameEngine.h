/**
	@file    gameEngine.h
	@brief   Itt tortenik az inputkezeles
**/
#pragma once

#include "map.h"
#include "character.h"
#include "items.h"
 /**
     @enum  gameState
     @brief Itt vannak eltarolva a jatekallasok
 **/
 enum class gameState { inGame,  inMenu, mapEditor, end, loading } ;

class gameEngine {
	gameState gameStateField;
public:

	gameEngine() :
		 gameStateField(gameState::inMenu) {}

	gameState getGameState() {
		return gameStateField;
	};
	void setGameState(gameState input) {
		gameStateField = input;
	};

	gameState menu();

	gameState startGame(terkep& mapOne, player& p, manaBat& b, archer& i, apple& a, superApple& s);

	~gameEngine() {}

};
