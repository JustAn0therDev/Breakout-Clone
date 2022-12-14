#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class RectangleEntity : public Entity {
public:
	sf::RectangleShape m_shape;

	RectangleEntity();
	RectangleEntity(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color);
};
