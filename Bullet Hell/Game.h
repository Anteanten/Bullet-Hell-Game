#ifndef  GAME_H
#define GAME_H
#include "Entity.h"
#include "Player.h"
#include "LevelHandler.h"
#include "StateManager.h"
#include "GameState.h"
#include "SFML\Graphics.hpp"

class Game : public GameState {
private:
	Player player;
	LevelHandler levelHandler;
	sf::Text text;
	sf::Font font;

	sf::Texture bulletTex;
public:
	Game(std::string levelName);
	~Game();

	void update( float deltaTime, StateManager &stateManager);
	void draw(sf::RenderWindow &window, float deltaTime);

};

#endif // ! GAME_H
