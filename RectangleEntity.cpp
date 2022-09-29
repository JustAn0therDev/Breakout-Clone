#include "RectangleEntity.hpp"
#include <SFML/Graphics.hpp>

RectangleEntity::RectangleEntity(const sf::Vector2f& size, const sf::Vector2f& pos) {
	m_shape = sf::RectangleShape();
	m_shape.setSize(size);
	m_shape.setPosition(pos);

	m_speed = 15.0f;
}

void RectangleEntity::Move(float delta_time) {
	m_shape.move(m_direction * m_speed * delta_time);
}