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

	Game();

	std::vector<Enemy*> makeEnemies(const EnemyType enemy_type, const float amount, const float y_pos);
};