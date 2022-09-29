#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
	sf::Vector2f m_direction;
	float m_speed;
	sf::Vector2f m_velocity;

	Entity();

	sf::Vector2f getVelocity() const;
};