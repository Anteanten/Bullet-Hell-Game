#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "SFML\Graphics.hpp"

class GameState {
private:


public:
	
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow &window, float deltaTime) = 0;
};

#endif