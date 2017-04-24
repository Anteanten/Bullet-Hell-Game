#ifndef  GAME_H
#define GAME_H
#include "GameState.h"
#include "Entity.h"
#include "Player.h"
#include "LevelHandler.h"
#include "SFML\Graphics.hpp"

class Game : public GameState{
private:
	Player player;
	LevelHandler levelHandler;

	sf::Texture bulletTex;

public:
	Game();

	void update( float deltaTime);
	void draw(sf::RenderWindow &window, float deltaTime);

};

#endif // ! GAME_H
