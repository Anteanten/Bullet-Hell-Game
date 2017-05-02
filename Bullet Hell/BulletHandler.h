#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H
#include "SFML\Graphics.hpp"
#include "Bullet.h"

enum State {ALIVE, DEAD};

class BulletHandler {
private:
	class Bullets{
	public:
		Bullet* bullet;
		State state;
		Bullets() {
			bullet = new Bullet();
			state = DEAD;
		}
	};
	Bullets** bullets;

	sf::VertexArray vertex;

	int capacity;

	void expand();
public:
	BulletHandler();

	void update(float deltaTime);

	sf::VertexArray getVertexArray();

	void addBullet(sf::Vector2f position, sf::Color color, sf::Texture texture, sf::IntRect rect, sf::Vector2f velocity);

};

#endif