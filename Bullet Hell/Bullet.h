#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

class Bullet : public Entity {
private:
	sf::Sprite sprite;

public:
	Bullet(sf::Vector2f position, sf::Color color, sf::Texture texture, sf::Vector2f velocity) {
		sprite.setPosition(position);
		sprite.setColor(color);
		sprite.setTexture(texture);
		this->velocity = velocity;
	}

	void update(float deltaTime) {
		sprite.setPosition(sprite.getPosition().x + velocity.x * deltaTime, sprite.getPosition().y + velocity.y * deltaTime);
	}

	sf::Sprite* getSprite() {
		return &sprite;
	}

};

#endif