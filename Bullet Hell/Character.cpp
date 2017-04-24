#include "Entity.h"

Entity::Entity() {
}

sf::Vector2f Entity::getPosition() const {
	return position;
}

sf::Vector2f Entity::getVelocity() const {
	return velocity;
}
