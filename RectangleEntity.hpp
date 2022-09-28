#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class RectangleEntity : public Entity {
	sf::RectangleShape m_shape;

	RectangleEntity(const sf::Vector2f& pos);
};
