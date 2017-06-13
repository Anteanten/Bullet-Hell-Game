#include "Game.h"

Game::Game(std::string levelName) {
	levelHandler.readLevelFile(levelName);
	bulletTex.loadFromFile("bullet.png");
	player.setBulletTexture(bulletTex);
	levelHandler.setBulletTex(bulletTex);
	font.loadFromFile("times.ttf");
	text.setFont(font);
	text.setPosition(10, 10);
	text.setCharacterSize(30);
}

Game::~Game() {
	bulletTex.~Texture();
}

void Game::update(float deltaTime, StateManager &stateManager) {
	player.update(deltaTime);
	player.checkCollision(deltaTime, levelHandler.getBulletHandler());
	levelHandler.update(deltaTime, player.getBulletHandler());
	levelHandler.playerPosition(player.getPos());
	text.setString("Health: " + std::to_string(player.getHealth()));
	if (player.getHealth() <= 0) {
		stateManager.pop();
	}
}

void Game::draw(sf::RenderWindow &window, float deltaTime) {
	levelHandler.draw(window);
	player.draw(window);
	window.draw(text);
}