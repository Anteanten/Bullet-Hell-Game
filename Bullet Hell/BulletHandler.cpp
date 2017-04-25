#include "BulletHandler.h"

void BulletHandler::expand() {
	capacity += 20;
	Bullet** temp = new Bullet*[capacity];
	for (int i = 0; i < capacity; i++) {
		temp[i] = bullets[i];
	}
	delete[] bullets;
	bullets = temp;
}

BulletHandler::BulletHandler() {
	capacity = 20;
	nrOfBullets = 0;
	bullets = new Bullet*[capacity];
	for (int i = 0; i < capacity; i++) {
		bullets[i] = nullptr;
	}
}

void BulletHandler::update(float deltaTime) {
	for (int i = 0; i < nrOfBullets; i++) {
		bullets[i]->update(deltaTime);
	}
	
}

void BulletHandler::addBullet(sf::Vector2f position, sf::Color color, sf::Texture texture, sf::Vector2f velocity) {
	if (nrOfBullets == capacity) {
		expand();
	}
	bullets[nrOfBullets++] = new Bullet(position, color, texture, velocity);
}