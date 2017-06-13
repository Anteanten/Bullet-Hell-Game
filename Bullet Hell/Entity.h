#ifndef ENTITY_H
#define ENTITY_H
enum State { ALIVE, DEAD };
#include "SFML\Graphics.hpp"

class Entity {
protected:
	sf::Vector2f position, velocity;

public:
	Entity();

	virtual void update(float deltaTime) = 0;
	
	sf::Vector2f getPos()const;
	sf::Vector2f getVelocity()const;

};

inline Entity::Entity(){
}

inline sf::Vector2f Entity::getPos()const {
	return position;
}

inline sf::Vector2f Entity::getVelocity() const {
	return velocity;
}

#endif // !CHARACTER_H
