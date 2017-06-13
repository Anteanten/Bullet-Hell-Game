#ifndef MENU_H
#define MENU_H
#include "Constants.h"
#include "StateManager.h"
#include "Game.h"

class Menu : public GameState{
private:
	sf::Text* text;
	sf::Font font;
	sf::Event event;

	int activeButton;
	int lowerButton;
	int upperButton;

	bool exitMenu;
	bool spacePressed;
	bool moveUpPressed;
	bool moveDownPressed;
	
	sf::RenderWindow *window;

public:
	Menu(sf::RenderWindow & window);
	~Menu();

	void update(float deltaTime, StateManager &stateManager);
	void draw(sf::RenderWindow &window, float deltaTime);
};

#endif