#include "EnemyHandler.h"
#include <math.h>
#include "Constants.h"

void EnemyHandler::expand() {
	capacity += 20;
	Enemies** temp = new Enemies*[capacity];
	for (int i = 0; i < capacity; i++) {
		if (i < capacity - 20) {
			temp[i] = enemies[i];
		} else {
			temp[i] = new Enemies();
		}
	}
	vertex.resize(capacity * 4);
	delete[] enemies;
	enemies = temp;
}

EnemyHandler::EnemyHandler() {
	capacity = 20;
	vertex.resize(capacity * 4);
	vertex.setPrimitiveType(sf::Quads);
	tex01.loadFromFile("drone.png");
	enemies = new Enemies*[capacity];
	for (int i = 0; i < capacity; i++) {
		enemies[i] = new Enemies();
	}
}

EnemyHandler::~EnemyHandler() {
	for (int i = 0; i < capacity; i++) {
		delete enemies[i]->enemy;
		delete enemies[i];
	}
	delete[] enemies;
}

void EnemyHandler::update(float deltaTime, BulletHandler *playerBullets, sf::Vector2f playerPos) {
	for (int i = 0; i < capacity; i++) {
		if (enemies[i] != nullptr) {
			if (enemies[i]->state == ALIVE) {
				enemies[i]->enemy->update(deltaTime);
				enemies[i]->enemy->updateBullet(&bulletHandler, tex, playerPos);
				checkBulletCollision(playerBullets);

				sf::Vertex* quad = &vertex[i * 4];
				sf::Sprite* spr = enemies[i]->enemy->getSprite();

				quad[0].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y);
				quad[1].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width, spr->getPosition().y);
				quad[2].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width, spr->getPosition().y + spr->getTextureRect().height);
				quad[3].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y + spr->getTextureRect().height);
				if (quad[0].position.x > WINDOW_WIDTH + 50 || quad[0].position.y > WINDOW_HEIGHT + 50 || quad[0].position.x < -50 || quad[0].position.y < -50) {
					enemies[i]->state = DEAD;
				}
			}
		}
	}
	bulletHandler.update(deltaTime);
}

void EnemyHandler::draw(sf::RenderWindow & window) {
	sf::Transform transform;
	sf::RenderStates state;
	state.transform = transform;
	state.texture = &tex;
	window.draw(*bulletHandler.getVertexArray(), state);
	state.texture = &tex01;
	window.draw(vertex, state);
}

void EnemyHandler::checkBulletCollision(BulletHandler *bulletHandler) {
	for (int j = 0; j < capacity; j++) {
		if (enemies[j]->state == ALIVE) {
			for (int i = 0; i < bulletHandler->getCapacity(); i++) {
				if (bulletHandler->getBulletState(i) == ALIVE) {
					if (enemies[j]->enemy->getSprite()->getGlobalBounds().intersects(bulletHandler->getBullet(i).getSprite()->getGlobalBounds())) {
						enemies[j]->enemy->hit();
						bulletHandler->killBullet(i);
					}
				}
			}
		}
	}
}

void EnemyHandler::setBulletTex(sf::Texture bulletTex) {
	tex = bulletTex;
}

void EnemyHandler::setEnemeyTex(sf::Texture tex) {
	tex01 = tex;
}

sf::VertexArray EnemyHandler::getVertexArray() {
	return vertex;
}

BulletHandler * EnemyHandler::getBulletHandler() {
	return &bulletHandler;
}

void EnemyHandler::addEnemy(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f bulletVelocity, sf::Texture texture, sf::IntRect rect, std::string fireType) {
	int count = 0;
	while (enemies[count]->state == ALIVE) {
		count++;
		if (count == capacity) {
			expand();
		}
	}
	enemies[count]->enemy->setEnemy(position, velocity, bulletVelocity, tex01, rect, fireType);

	// Get the quad contained in the vertex array
	sf::Vertex* quad = &vertex[count * 4];
	sf::Sprite *spr = enemies[count]->enemy->getSprite();

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

	enemies[count]->state = ALIVE;
}
