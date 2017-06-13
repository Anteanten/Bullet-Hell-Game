#include "BulletHandler.h"
#include <iostream>
#include "Constants.h"

void BulletHandler::expand() {
	capacity += 20;
	Bullets** temp = new Bullets*[capacity];
	for (int i = 0; i < capacity; i++) {
		if (i < capacity - 20) {
			temp[i] = bullets[i];
		} else {
			temp[i] = new Bullets();
		}
	}
	vertex.resize(capacity * 4);
	delete[] bullets;
	bullets = temp;
}

BulletHandler::BulletHandler() {
	capacity = 20;
	vertex.resize(capacity * 4);
	vertex.setPrimitiveType(sf::Quads);
	bullets = new Bullets*[capacity];
	for (int i = 0; i < capacity; i++) {
		bullets[i] = new Bullets();
	}
}

BulletHandler::~BulletHandler() {
	for (int i = 0; i < capacity; i++) {
		delete bullets[i]->bullet;
		delete bullets[i];
	}
	delete[] bullets;
}

void BulletHandler::update(float deltaTime) {
	for (int i = 0; i < capacity; i++) {
		if (bullets[i] != nullptr) {
			if (bullets[i]->state == ALIVE) {
				bullets[i]->bullet->update(deltaTime);

				sf::Vertex* quad = &vertex[i * 4];
				sf::Sprite* spr = bullets[i]->bullet->getSprite();

				quad[0].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y);
				quad[1].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width, spr->getPosition().y);
				quad[2].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width, spr->getPosition().y + spr->getTextureRect().height);
				quad[3].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y + spr->getTextureRect().height);
				if (quad[0].position.x > WINDOW_WIDTH + 50 || quad[0].position.y > WINDOW_HEIGHT + 50 || quad[0].position.x < -50 || quad[0].position.y < -50) {
					bullets[i]->state = DEAD;
				}
			}
		}
	}
}

sf::VertexArray* BulletHandler::getVertexArray() {
	return &vertex;
}

int BulletHandler::getCapacity() const {
	return capacity;
}

Bullet BulletHandler::getBullet(int index) const {
	return *bullets[index]->bullet;
}

State BulletHandler::getBulletState(int index) const {
	return bullets[index]->state;
}

void BulletHandler::killBullet(int index) {
	bullets[index]->bullet->kill();
}

void BulletHandler::addBullet(sf::Vector2f position, sf::Color color, sf::Texture &texture, sf::IntRect rect, sf::Vector2f velocity) {
	int count = 0;
	while (bullets[count]->state == ALIVE) {
		count++;
		if (count == capacity) {
			expand();
		}
	}
	bullets[count]->bullet->setBullet(position, color, texture, rect, velocity);

	// Get the quad contained in the vertex array
	sf::Vertex* quad = &vertex[count * 4];
	sf::Sprite* spr = bullets[count]->bullet->getSprite();

	// Set the position of the sprite
	quad[0].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y);
	quad[1].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width,
		spr->getPosition().y);
	quad[2].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width,
		spr->getPosition().y + spr->getTextureRect().height);
	quad[3].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y +
		spr->getTextureRect().height);

	// Set the texture of the sprite
	quad[0].texCoords = sf::Vector2f(spr->getTextureRect().left, spr->getTextureRect().top);
	quad[1].texCoords = sf::Vector2f(spr->getTextureRect().left + spr->getTextureRect().width,
		spr->getTextureRect().top);
	quad[2].texCoords = sf::Vector2f(spr->getTextureRect().left + spr->getTextureRect().width,
		spr->getTextureRect().top + spr->getTextureRect().height);
	quad[3].texCoords = sf::Vector2f(spr->getTextureRect().left, spr->getTextureRect().top +
		spr->getTextureRect().height);

	bullets[count]->state = ALIVE;
}