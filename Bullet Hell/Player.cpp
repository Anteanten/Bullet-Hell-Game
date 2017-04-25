#include "Player.h"

void Player::controll() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		velocity.y = -300;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x = 500;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		velocity.y = 300;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x = -500;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletTimer <= 0) {
		bulletHandler.addBullet(player[1].position, sf::Color(255, 0, 0, 255), tex, sf::Vector2f(0, -200));
		bulletTimer = 0.25;
	}
}

Player::Player() {
	player = sf::VertexArray(sf::Triangles, 3);
	player[0].position = sf::Vector2f(15, 50);
	player[1].position = sf::Vector2f(30, 10);
	player[2].position = sf::Vector2f(45, 50);
	player[0].color = sf::Color(0, 255, 0, 255);
	player[1].color = sf::Color(255, 0, 0, 255);
	player[2].color = sf::Color(0, 0, 255, 255);
}

void Player::update(float deltaTime) {
	controll();
	//Change the position of the verticies
	for (int i = 0; i < 3; i++) {
		player[i].position += velocity * deltaTime;
	}
	bulletHandler.update(deltaTime);
	//Set the veloctity to 0 so player don't move if the buttons are not pressed
	velocity.x = 0;
	velocity.y = 0;
}

void Player::draw(sf::RenderWindow &window) {
	window.draw(player);
}

sf::VertexArray Player::getVertex() {
	return player;
}

void Player::setBulletTexture(sf::Texture tex) {
	this->tex = tex;
}
