#include "Entity.h"
#include "BulletHandler.h"
#include "Constants.h"
#include <math.h>
#include <iostream>


class Enemy : public Entity {
private:
	sf::Sprite sprite;
	std::string fireType;
	sf::Vector2f bulletVelocity;
	float maxBulletVelocity;
	float fireTimer;
	int health;

public:
	Enemy() {}
	void setEnemy(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f bulletVelocity, sf::Texture texture, sf::IntRect rect, std::string fireType) {
		this->velocity = velocity;
		this->bulletVelocity = bulletVelocity;
		sprite.setPosition(position);
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		fireTimer = 0;
		health = 5;
		this->fireType = fireType;
		maxBulletVelocity = abs(bulletVelocity.x) + abs(bulletVelocity.y);
	}
	void update(float deltaTime) {
		sprite.setPosition(sprite.getPosition().x + velocity.x * deltaTime, sprite.getPosition().y + velocity.y * deltaTime);
		position = sprite.getPosition();
		fireTimer += deltaTime;
		
	}

	void updateBullet(BulletHandler *bulletHandler, sf::Texture bulletTexture, sf::Vector2f playerPos) {
		if (fireTimer >= 1) {
			fireTimer = 0;
			if (fireType == "track") {
				//Find how much time it takes for maxVel to reach. Then use v = s/t to get x and y speed
				float max = sqrt(pow((playerPos.x - position.x), 2) + pow((playerPos.y - position.y), 2)) / maxBulletVelocity;
				bulletVelocity.x = (playerPos.x - position.x) / max;
				bulletVelocity.y = (playerPos.y - position.y) / max;
			}
			bulletHandler->addBullet(sprite.getPosition(), sf::Color(255, 0, 255), bulletTexture, sf::IntRect(0, 0, 4, 16), bulletVelocity);
		}
	}

	void hit() {
		health--;
		if (health <= 0) {
			sprite.setPosition(-500, -400);
		}
	}


	sf::Sprite* getSprite() {
		return &sprite;
	}
};