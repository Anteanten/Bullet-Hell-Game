#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

class Bullet : public Entity {
private:
	sf::Sprite sprite;

public:
	Bullet() {
	}

	void setBullet(sf::Vector2f position, sf::Color color, sf::Texture texture, sf::IntRect rect, sf::Vector2f velocity) {
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		sprite.setColor(color);
		sprite.setPosition(position);
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