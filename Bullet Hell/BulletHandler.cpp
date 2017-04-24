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
		if (bullets[i]->getPosition().x > 1000 || bullets[i]->getPosition().y > 1000 || bullets[i]->getPosition().x < 0 || bullets[i]->getPosition().y < 0) {
			delete bullets[i];
			for (int j = i; j < nrOfBullets - 1; j++) {
				bullets[j] = bullets[j + 1];
			}
				nrOfBullets--;
		}
	}
	
}

void BulletHandler::addBullet(sf::Vector2f position, sf::Color color, sf::Texture texture, sf::Vector2f velocity) {
	if (nrOfBullets == capacity) {
		expand();
	}
	bullets[nrOfBullets++] = new Bullet(position, color, texture, velocity);
}