#include "LevelHandler.h"
#define BACKGROUND_HEIGHT 700

LevelHandler::LevelHandler() {
	background.loadFromFile("background.png");
	backgroundSprite = new sf::Sprite[2];
	for (int i = 0; i < 2; i++) {
		backgroundSprite[i].setTexture(background);
		backgroundSprite[i].setPosition(0, -BACKGROUND_HEIGHT * i + 2);
	}
	backgroundSprite[1].rotate(180);
	backgroundSprite[1].setScale(-1, 1);
	backgroundSprite[1].setOrigin(0, BACKGROUND_HEIGHT);
}
LevelHandler::~LevelHandler() {
	delete[] enemySpawn;
	delete[] backgroundSprite;
	background.~Texture();
}
void LevelHandler::update(float deltaTime, BulletHandler *playerBulletHandler) {
	enemyHandler.update(deltaTime, playerBulletHandler, playerPos);
	levelTime += deltaTime;
	for (int i = 0; i < 2; i++) {
		backgroundSprite[i].move(0, 200 * deltaTime);
		if (backgroundSprite[i].getPosition().y >= WINDOW_HEIGHT) {
			backgroundSprite[i].setPosition(0, backgroundSprite[i + (1 - i * 2)].getPosition().y - BACKGROUND_HEIGHT + 2);
		}
	}
	for (int i = currentSpawn; i < nrOfSpawns; i++) {
		if (enemySpawn[i].spawnStart <= levelTime) {
			if (enemySpawn[i].spawnInterval * enemySpawn[i].amountSpawned <= enemySpawn[i].activeTime) {
				enemyHandler.addEnemy(sf::Vector2f(enemySpawn[i].xPos, enemySpawn[i].yPos), sf::Vector2f(enemySpawn[i].xVel, enemySpawn[i].yVel), sf::Vector2f(enemySpawn[i].xBulVel, enemySpawn[i].yBulVel),enemySpawn[i].texture, sf::IntRect(0, 0, 32, 32), enemySpawn[i].fireType);
				if (++enemySpawn[i].amountSpawned == enemySpawn[i].amount) {
					currentSpawn++;
				}
			}
			enemySpawn[i].activeTime += deltaTime;
		}
	}
}

void LevelHandler::draw(sf::RenderWindow & window) {
	sf::Transform transform;
	sf::RenderStates state;
	state.transform = transform;
	state.texture = &background;
	for (int i = 0; i < 2; i++) {
		window.draw(backgroundSprite[i], state);
	}
	enemyHandler.draw(window);
}

void LevelHandler::readLevelFile(std::string filename) {
	std::ifstream file;
	file.open(filename);
	std::string line;
	int count = 0;
	if (file.is_open()) {
		std::getline(file, line);
		enemySpawn = new EnemySpawn[std::stoi(line)];
		while (std::getline(file, line)) {
			if (line == "enemy = {") {
				bool creatingEnemy = true;
				while (creatingEnemy) {
					std::getline(file, line, '=');
					line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
					line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
					line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
					if (line == "health") {
						std::getline(file, line, ';');
						enemySpawn[count].health = std::stoi(line);
					} else if (line == "amount") {
						std::getline(file, line, ';');
						enemySpawn[count].amount = std::stoi(line);
					} else if (line == "texture") {
						std::getline(file, line, ';');
						enemySpawn[count].texture.loadFromFile(line);
					} else if (line == "fireType") {
						std::getline(file, line, ';');
						line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
						enemySpawn[count].fireType = line;
					} else if (line == "spawnStart") {
						std::getline(file, line, ';');
						enemySpawn[count].spawnStart = std::stof(line);
					} else if (line == "spawnInterval") {
						std::getline(file, line, ';');
						enemySpawn[count].spawnInterval = std::stof(line);
					} else if (line == "xPosition") {
						std::getline(file, line, ';');
						enemySpawn[count].xPos = std::stof(line);
					} else if (line == "yPosition") {
						std::getline(file, line, ';');
						enemySpawn[count].yPos = std::stof(line);
					} else if (line == "xVelocity") {
						std::getline(file, line, ';');
						enemySpawn[count].xVel = std::stof(line);
					} else if (line == "yVelocity") {
						std::getline(file, line, ';');
						enemySpawn[count].yVel = std::stof(line);
					} else if (line == "xBulletVelocity") {
						std::getline(file, line, ';');
						enemySpawn[count].xBulVel = std::stof(line);
					} else if (line == "yBulletVelocity") {
						std::getline(file, line, ';');
						enemySpawn[count].yBulVel = std::stof(line);
					} else if (line == "}") {
						creatingEnemy = false;
						count++;
					}
				}
			}
		}
	}
	nrOfSpawns = count;
	file.close();
}

BulletHandler * LevelHandler::getBulletHandler() {
	return enemyHandler.getBulletHandler();
}

void LevelHandler::setBulletTex(sf::Texture bulletTex) {
	enemyHandler.setBulletTex(bulletTex);
}

void LevelHandler::playerPosition(sf::Vector2f pos) {
	playerPos = pos;
}

