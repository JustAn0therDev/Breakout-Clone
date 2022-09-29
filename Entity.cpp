#include "Entity.hpp"

Entity::Entity() : m_speed(5) {

}

sf::Vector2f Entity::getVelocity() const {
	return m_direction * m_speed;
}