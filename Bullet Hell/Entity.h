#ifndef ENTITY_H
#define ENTITY_H
#include "SFML\Graphics.hpp"

class Entity {
protected:
	sf::Vector2f position, velocity;

public:
	Entity();

	virtual void update(float deltaTime) = 0;
	
	sf::Vector2f getPosition()const;
	sf::Vector2f getVelocity()const;

};

Entity::Entity(){
}

sf::Vector2f Entity::getPosition()const {
	return position;
}

inline sf::Vector2f Entity::getVelocity() const {
	return velocity;
}

#endif // !CHARACTER_H
