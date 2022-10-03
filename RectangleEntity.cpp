#include "RectangleEntity.hpp"
#include <SFML/Graphics.hpp>

RectangleEntity::RectangleEntity(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color) {
	m_shape = sf::RectangleShape();
	m_shape.setSize(size);
	m_shape.setPosition(pos);
	m_shape.setFillColor(color);

	m_speed = 20.0f;
}

RectangleEntity::RectangleEntity() { }