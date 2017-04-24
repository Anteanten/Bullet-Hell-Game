#include "Game.h"

Game::Game() {
	bulletTex.loadFromFile("bullet.png");
	player.setBulletTexture(bulletTex);
}

void Game::update(float deltaTime) {
	player.update(deltaTime);
}

void Game::draw(sf::RenderWindow &window, float deltaTime) {
	player.draw(window);
}
