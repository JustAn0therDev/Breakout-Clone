#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class CircleEntity : public Entity {
public:
	sf::CircleShape m_shape;

	CircleEntity(const sf::Vector2f& pos);
};