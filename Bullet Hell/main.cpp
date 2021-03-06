#include <SFML\Graphics.hpp>
#include "StateManager.h"
#include "Game.h"
#include "Menu.h"
#include <iostream>
#include "Constants.h"
#include <crtdbg.h>

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pew Pew");
	StateManager stateManager;
	sf::Time time;
	sf::Clock clock;
	float checkTime = 0;
	int fps = 0;

	//Push a new Game object
	stateManager.push(new Menu(window));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		time = clock.restart();
		checkTime += time.asSeconds();
		fps++;
		//Dont run if a prolonged pause
		if (time.asSeconds() < 1) {
			//Try incase the stack is empty
			try {
				//Call the top stacked gamestate
				stateManager.peek()->update(time.asSeconds(), stateManager);
				stateManager.peek()->draw(window, time.asSeconds());
			} catch (char* e) {
				window.close();
				std::cout << e << std::endl;
			}
		}
		if (checkTime >= 1) {
			std::cout << "FPS: " + std::to_string(fps) << std::endl;
			fps = 0;
			checkTime = 0;
		}
 		window.display();
	}
	window.~RenderWindow();
	return 0;
}