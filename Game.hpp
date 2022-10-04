#pragma once
#include "RectangleEntity.hpp"
#include "CircleEntity.hpp"
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>

class Game {
public:
	RectangleEntity m_ceiling;
	RectangleEntity m_rightWall;
	RectangleEntity m_leftWall;
	RectangleEntity m_playerEntity;
	CircleEntity m_ball;

	std::vector<Enemy*> m_frontlineEnemies;
	std::vector<Enemy*> m_middlelineEnemies;
	std::vector<Enemy*> m_backlineEnemies;

	sf::Text m_restartText;
	sf::Color m_restartTextColor;

	Game(const sf::Font& font);

	std::vector<Enemy*> makeEnemies(const EnemyType enemy_type, const float amount, const float y_pos);
	bool ballIsOutOfBounds();
};