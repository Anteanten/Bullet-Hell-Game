#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H
#include "Constants.h"
#include "EnemyHandler.h"
#include "BulletHandler.h"
#include <iostream>
#include <fstream>

class LevelHandler {
private:
	class EnemySpawn {
	public:
		float spawnInterval;
		float spawnStart;
		float activeTime = 0;
		float xPos, yPos;
		float xVel, yVel;
		float xBulVel, yBulVel;

		std::string fireType;

		sf::Texture texture;

		int health;
		int amount;
		int amountSpawned = 0;

		~EnemySpawn() {
			texture.~Texture();
		}
	};

	EnemyHandler enemyHandler;
	EnemySpawn* enemySpawn;

	float levelTime;
	int count;
	int nrOfSpawns;
	int currentSpawn;

	sf::Vector2f playerPos;

	sf::Texture tex01;
	sf::Texture bulletTex;
	sf::Texture background;

	sf::Sprite* backgroundSprite;
public:
	LevelHandler();
	~LevelHandler();

	void update(float deltaTime, BulletHandler *playerBulletHandler);
	void draw(sf::RenderWindow &window);

	void readLevelFile(std::string filename);

	BulletHandler* getBulletHandler();
	
	void setBulletTex(sf::Texture bulletTex);
	void playerPosition(sf::Vector2f pos);
};

#endif