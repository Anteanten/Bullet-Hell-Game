#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "BulletHandler.h"

class Player : public Entity{
private:
	
	BulletHandler bulletHandler;
	sf::VertexArray player;
	sf::Texture tex;

	int uppgradeLevel;
	int health;
	float bulletTimer;
	float invincibleTimer;

	void controll();

public:
	Player();
	~Player();

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	void checkCollision(float deltaTime, BulletHandler *enemyBullets);

	sf::VertexArray getVertex();
	BulletHandler *getBulletHandler();
	int getHealth() const;

	void setBulletTexture(sf::Texture tex);

};

#endif // !PLAYER_H
