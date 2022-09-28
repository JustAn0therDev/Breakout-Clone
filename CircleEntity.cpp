#include "CircleEntity.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

CircleEntity::CircleEntity(const sf::Vector2f& pos) {
	m_pos = pos;
	m_direction = sf::Vector2f(1, 0);
	m_shape = sf::CircleShape();
	m_speed = 5.0f;

	m_shape.setPosition(m_pos);
}
