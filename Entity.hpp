#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
	sf::Vector2f m_pos;
	sf::Vector2f m_direction;
	float m_speed;

	Entity();

	sf::Vector2f getMoveOffset() const {
		return m_direction * m_speed;
	}
};