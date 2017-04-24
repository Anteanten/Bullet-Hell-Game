#include "Bullet.h"

Bullet::Bullet() {
}

Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity, float size, sf::Color color) {
	this->velocity = velocity;
	this->color = color;
	int radius = 2;
	bullet = 
	
}

void Bullet::update(float deltaTime) {
	for (int i = 0; i < 5; i++) {
		bullet[i].position += velocity * deltaTime;
	}
}

sf::Vector2f Bullet::getPosition() const {
	return bullet[0].position;
}

sf::Vertex* Bullet::getVertex() const {
	return bullet;
}
