#include "CircleEntity.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

CircleEntity::CircleEntity() {
	
}

CircleEntity::CircleEntity(float radius, const sf::Vector2f& pos) {
	m_direction = sf::Vector2f(0.5f, 0.5f);

	m_shape = sf::CircleShape();
	m_shape.setRadius(radius);
	m_shape.setPosition(pos);

	m_speed = 30.0f;
}

