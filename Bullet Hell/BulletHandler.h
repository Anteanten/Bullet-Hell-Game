#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H
#include "SFML\Graphics.hpp"
#include "Bullet.h"

class BulletHandler {
private:
	Bullet **bullets;

	int capacity;
	int nrOfBullets;

	void expand();
public:
	BulletHandler();

	void update(float deltaTime);

	void addBullet(sf::Vector2f position, sf::Color color, sf::Texture texture, sf::Vector2f velocity);

};

#endif