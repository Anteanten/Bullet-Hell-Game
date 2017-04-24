#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "SFML\Graphics.hpp"
#include "BulletHandler.h"

class Player : public Entity{
private:
	BulletHandler bulletHandler;

	void controll();
	sf::VertexArray player;
	sf::Texture tex;

	float bulletTimer;

public:
	Player();

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	sf::VertexArray getVertex();

	void setBulletTexture(sf::Texture tex);

};

#endif // !PLAYER_H
