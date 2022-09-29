#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class RectangleEntity : public Entity {
public:
	sf::RectangleShape m_shape;

	RectangleEntity(const sf::Vector2f& size, const sf::Vector2f& pos);
	void Move(float delta_time);
};
