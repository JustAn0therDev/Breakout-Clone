#include "Enemy.hpp"
#include "EnemyType.hpp"
#include "RectangleEntity.hpp"

void Enemy::updateColorByHealth() {
	if (m_health == (int)EnemyType::Weak) {
		m_color = sf::Color::White;
	}
	else if (m_health == (int)EnemyType::Normal) {
		m_color = sf::Color::Blue;
	}
	else {
		m_color = sf::Color::Red;
	}

	m_rectangle_entity.m_shape.setFillColor(m_color);
}

Enemy::Enemy(const EnemyType& enemy_type, const sf::Vector2f& rectangle_size, const sf::Vector2f& position) {
	m_health = static_cast<int>(enemy_type);
	updateColorByHealth();
	m_rectangle_entity = RectangleEntity(rectangle_size, position, m_color);
}

void Enemy::takeDamage() {
	m_health--;
	updateColorByHealth();
}