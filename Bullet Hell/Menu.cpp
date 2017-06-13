#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow & window) {
	spacePressed = false;
	moveUpPressed = false;
	moveDownPressed = false;

	exitMenu = false;

	lowerButton = 0;
	upperButton = 1;

	font.loadFromFile("times.ttf");
	text = new sf::Text [5];
	this->window = &window;
	text[0].setString("Play");
	text[1].setString("Exit");
	text[2].setString("Level 1");
	text[3].setString("Level 2");
	text[4].setString("Back");
	for (int i = 0; i < 2; i++) {
		text[i].setCharacterSize(30);
		text[i].setFont(font);
		text[i].setStyle(sf::Text::Bold);
		text[i].setPosition(sf::Vector2f((WINDOW_WIDTH - text[i].getGlobalBounds().width) / 2, WINDOW_HEIGHT / 4 * (i + 1)));
	}
	for (int i = 2; i < 5; i++) {
		text[i].setCharacterSize(30);
		text[i].setFont(font);
		text[i].setStyle(sf::Text::Bold);
		text[i].setPosition(sf::Vector2f((WINDOW_WIDTH - text[i].getGlobalBounds().width) / 2, WINDOW_HEIGHT/ 4 * (i - 1)));
	}
}

Menu::~Menu() {
	delete[] text;
}

void Menu::update(float deltaTime, StateManager &stateManager) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		moveUpPressed = true;
	} else {
		if (moveUpPressed) {
			moveUpPressed = false;
			activeButton--;
			if (activeButton < lowerButton) {
				activeButton = lowerButton;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		moveDownPressed = true;
	} else {
		if (moveDownPressed) {
			moveDownPressed = false;
			activeButton++;
			if (activeButton > upperButton) {
				activeButton = upperButton;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		spacePressed = true;
	} else {
		if (spacePressed) {
			spacePressed = false;
			if (activeButton == 0 || activeButton == 4) {
				if (upperButton == 1) {
					activeButton = 2;
					lowerButton = 2;
					upperButton = 4;
				} else {
					activeButton = 0;
					upperButton = 1;
					lowerButton = 0;
				}
			} else if (activeButton == 1) {
				stateManager.pop();
			} else if (activeButton == 2) {
				stateManager.push(new Game("level01.txt"));
			} else if (activeButton == 3) {
				stateManager.push(new Game("Level02.txt"));
			}
		}
	}
	switch (activeButton) {
	case 0: {
		text[0].setFillColor(sf::Color::Red);
		text[1].setFillColor(sf::Color::White);
		break;
	}
	case 1: {
		text[0].setFillColor(sf::Color::White);
		text[1].setFillColor(sf::Color::Red);
		break;
	}
	case 2: {
		text[2].setFillColor(sf::Color::Red);
		text[3].setFillColor(sf::Color::White);
		text[4].setFillColor(sf::Color::White);
		break;
	}
	case 3: {
		text[2].setFillColor(sf::Color::White);
		text[3].setFillColor(sf::Color::Red);
		text[4].setFillColor(sf::Color::White);
		break;
	}
	case 4: {
		text[2].setFillColor(sf::Color::White);
		text[3].setFillColor(sf::Color::White);
		text[4].setFillColor(sf::Color::Red);
		break;
	}
	}
}

void Menu::draw(sf::RenderWindow & window, float deltaTime) {
	for (int i = lowerButton; i <= upperButton; i++) {
		window.draw(text[i]);
	}
}

