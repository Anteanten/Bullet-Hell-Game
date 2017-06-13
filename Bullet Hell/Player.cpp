#include "Player.h"
#include "Constants.h"

void Player::controll() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		velocity.y = -250;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x = 400;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		velocity.y = 250;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x = -400;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletTimer <= 0) {
		switch (uppgradeLevel) {
		case 1: {
			bulletHandler.addBullet(sf::Vector2f(player[1].position.x - 2, player[1].position.y), sf::Color(255, 0, 255), tex, sf::IntRect(0, 0, 4, 16), sf::Vector2f(0, -400));
			bulletTimer = 0.2f;
			break;
		}
		case 2: {
			bulletHandler.addBullet(sf::Vector2f(player[1].position.x + 4, player[1].position.y), sf::Color(255, 0, 255), tex, sf::IntRect(0, 0, 4, 16), sf::Vector2f(0, -400));
			bulletHandler.addBullet(sf::Vector2f(player[1].position.x - 8, player[1].position.y), sf::Color(255, 0, 255), tex, sf::IntRect(0, 0, 4, 16), sf::Vector2f(0, -400));
			bulletTimer = 0.2f;
			break;
		}
		case 3: {
			bulletHandler.addBullet(sf::Vector2f(player[1].position.x + 4, player[1].position.y), sf::Color(255, 0, 255), tex, sf::IntRect(0, 0, 4, 16), sf::Vector2f(0, -400));
			bulletHandler.addBullet(sf::Vector2f(player[1].position.x - 8, player[1].position.y), sf::Color(255, 0, 255), tex, sf::IntRect(0, 0, 4, 16), sf::Vector2f(0, -400));
			bulletHandler.addBullet(sf::Vector2f(player[1].position.x + 4, player[1].position.y), sf::Color(255, 0, 255), tex, sf::IntRect(0, 0, 4, 16), sf::Vector2f(50, -400));
			bulletHandler.addBullet(sf::Vector2f(player[1].position.x - 8, player[1].position.y), sf::Color(255, 0, 255), tex, sf::IntRect(0, 0, 4, 16), sf::Vector2f(-50, -400));
			bulletTimer = 0.2f;
			break;
		}
		}
	}
}

void Player::checkCollision(float deltaTime, BulletHandler *enemyBullets) {
	if (invincibleTimer <= 0) {
		for (int i = 0; i < enemyBullets->getCapacity(); i++) {
			if (enemyBullets->getBulletState(i) == ALIVE) {
				if (player.getBounds().intersects(enemyBullets->getBullet(i).getSprite()->getGlobalBounds())) {
					health--;
					enemyBullets->killBullet(i);
					invincibleTimer = 2;
				}
			}
		}
	} else if(invincibleTimer > 0){
		invincibleTimer -= deltaTime;
	}
}

Player::Player() {
	player = sf::VertexArray(sf::Triangles, 3);
	int x = WINDOW_WIDTH / 2;
	int y = WINDOW_HEIGHT / 2;
	player[0].position = sf::Vector2f(x + 20, y + 40);
	player[1].position = sf::Vector2f(x + 30, y + 10);
	player[2].position = sf::Vector2f(x + 40, y + 40);
	player[0].color = sf::Color(0, 255, 0, 255);
	player[1].color = sf::Color(255, 0, 0, 255);
	player[2].color = sf::Color(0, 0, 255, 255);
	invincibleTimer = 0;
	health = 1;
	uppgradeLevel = 3;
}

Player::~Player() {
}

void Player::update(float deltaTime) {
	controll();
	//Change the position of the verticies
	for (int i = 0; i < 3; i++) {
		player[i].position += velocity * deltaTime;
		position.x = player[1].position.x;
		position.y = player[1].position.y + (player[0].position.y - player[1].position.y)/2;
	}
	if (bulletTimer > 0) {
		bulletTimer -= deltaTime;
	}
	bulletHandler.update(deltaTime);
	//Set the veloctity to 0 so player don't move if the buttons are not pressed
	velocity.x = 0;
	velocity.y = 0;
}

void Player::draw(sf::RenderWindow &window) {
  	window.draw(player);
	sf::Transform transform;
	sf::RenderStates state;
	state.transform = transform;
	state.texture = &tex;
	window.draw(*bulletHandler.getVertexArray(), state);
}

sf::VertexArray Player::getVertex() {
	return player;
}

BulletHandler* Player::getBulletHandler() {
	return &bulletHandler;
}

int Player::getHealth() const {
	return health;
}

void Player::setBulletTexture(sf::Texture tex) {
	this->tex = tex;
}
