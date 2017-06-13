#include "Enemy.h"
#include "BulletHandler.h"

class EnemyHandler {
private:
	class Enemies {
	public:
		Enemy* enemy;
		State state;
		Enemies() {
			enemy = new Enemy();
			state = DEAD;
		}
	};
	Enemies** enemies;
	BulletHandler bulletHandler;

	sf::VertexArray vertex;

	sf::Vector2f playerPos;

	sf::Texture tex;
	sf::Texture tex01;

	int capacity;

	void expand();
public:
	EnemyHandler();
	~EnemyHandler();

	void update(float deltaTime, BulletHandler *playerBullets, sf::Vector2f playerPos);
	void draw(sf::RenderWindow &window);

	void checkBulletCollision(BulletHandler *bulletHandler);

	void setBulletTex(sf::Texture bulletTex);
	void setEnemeyTex(sf::Texture tex);

	sf::VertexArray getVertexArray();
	BulletHandler* getBulletHandler();

	void addEnemy(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f bulletVelocity, sf::Texture texture, sf::IntRect rect, std::string fireType);
};