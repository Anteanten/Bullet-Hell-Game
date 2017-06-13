#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "StateManager.h"
#include "SFML\Graphics.hpp"

class GameState {
public:
	virtual ~GameState() = 0;
	virtual void update(float deltaTime, StateManager &stateManager) = 0;
	virtual void draw(sf::RenderWindow &window, float deltaTime) = 0;
};

inline GameState::~GameState(){}

#endif