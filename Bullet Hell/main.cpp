#include <SFML\Graphics.hpp>
#include "StateManager.h"
#include "Game.h"
#include "GameState.h"
#include <iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pew Pew");
	StateManager stateManager;
	sf::Time time;
	sf::Clock clock;
	float checkTime = 0;
	int fps = 0;

	//Push a new Game object
	stateManager.push(new Game);
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

		//Try incase the stack is empty
		try {
			//Call the top stacked gamestate
			stateManager.peek()->update(time.asSeconds());
			stateManager.peek()->draw(window, time.asSeconds());
		} catch (char* e) {
			std::cout << e << std::endl;
		}
		if (checkTime >= 1) {
			std::cout << "FPS: " + std::to_string(fps) << std::endl;
			fps = 0;
			checkTime = 0;
		}
		window.display();
	}

	return 0;
}