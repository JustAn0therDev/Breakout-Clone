#include "CircleEntity.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

CircleEntity::CircleEntity(float radius, const sf::Vector2f& pos) {
	m_direction = sf::Vector2f(1, 0);

	m_shape = sf::CircleShape();
	m_shape.setRadius(radius);
	m_shape.setPosition(pos);

	m_speed = 0.05f;
}

void CircleEntity::Move(float delta_time) {
	m_shape.move(m_direction * m_speed * delta_time);
}
