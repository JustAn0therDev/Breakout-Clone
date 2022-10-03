#pragma once
#include "RectangleEntity.hpp"
#include "EnemyType.hpp"

class Enemy {
private:
	void updateColorByHealth();
public:
	int m_health;
	sf::Color m_color;
	RectangleEntity m_rectangle_entity;

	Enemy(const EnemyType& enemy_type, const sf::Vector2f& rectangle_size, const sf::Vector2f& position);

	void takeDamage();
};