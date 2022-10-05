#include "Game.hpp"
#include "RectangleEntity.hpp"
#include "CircleEntity.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"
#include "EnemyType.hpp"

Game::Game(const sf::Font& font) {
	m_playerEntity = RectangleEntity(sf::Vector2f(WINDOW_WIDTH / 4, 10), sf::Vector2f((WINDOW_WIDTH / 2) + (WINDOW_WIDTH / 4), WINDOW_HEIGHT - 20), sf::Color::Magenta);

	m_ball = CircleEntity(BALL_RADIUS, sf::Vector2f((WINDOW_WIDTH / 2) - BALL_RADIUS, (WINDOW_HEIGHT / 2) - BALL_RADIUS));
	m_ball.m_shape.setFillColor(sf::Color::Blue);

	m_rightWall = RectangleEntity(sf::Vector2f(1, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH - 1, 1), sf::Color::White);

	m_leftWall = RectangleEntity(sf::Vector2f(1, WINDOW_HEIGHT), sf::Vector2f(0, 0), sf::Color::White);

	m_ceiling = RectangleEntity(sf::Vector2f(WINDOW_WIDTH, 1), sf::Vector2f(0, 0), sf::Color::White);

	m_backlineEnemies = makeEnemies(EnemyType::Strong, 5, 80);
	m_middlelineEnemies = makeEnemies(EnemyType::Normal, 5, 120);
	m_frontlineEnemies = makeEnemies(EnemyType::Weak, 7, 160);

	m_textColor = sf::Color(255, 255, 255, 0);

	m_restartText.setFont(font);
	m_restartText.setCharacterSize(24);
	m_restartText.setFillColor(m_textColor);
	m_restartText.setString("restarting");
	m_restartText.setPosition((WINDOW_WIDTH / 2.0f) - m_restartText.getCharacterSize() * 5, WINDOW_HEIGHT / 2.0f);

	m_gameOverText.setFont(font);
	m_gameOverText.setCharacterSize(24);
	m_gameOverText.setFillColor(sf::Color::White);
	m_gameOverText.setString("you win!");
	m_gameOverText.setPosition((WINDOW_WIDTH / 2.0f) - m_restartText.getCharacterSize() * 3, WINDOW_HEIGHT / 2.0f);
}

std::vector<Enemy*> Game::makeEnemies(const EnemyType enemy_type, const float amount, const float y_pos) {
	std::vector<Enemy*> enemies;
	enemies.reserve(static_cast<int>(amount));

	float size = (WINDOW_WIDTH / amount) - 10 * 2;

	float space_between = (WINDOW_WIDTH - (size * amount)) / (amount + 1);

	float pos = space_between;

	for (int i = 0; i < static_cast<int>(amount); i++) {
		Enemy* enemy = new Enemy(enemy_type, sf::Vector2f(size, 20), sf::Vector2f(pos, y_pos));
		enemy->m_rectangle_entity.m_direction.x = 1;
		enemies.emplace_back(enemy);
		pos += size + space_between;
	}

	return enemies;
}

bool Game::ballIsOutOfBounds() {
	return m_ball.m_shape.getPosition().y + m_ball.m_shape.getGlobalBounds().height > WINDOW_HEIGHT;
}

bool Game::isOver() {
	bool isOver = true;

	for (const auto& ptr : m_backlineEnemies) {
		if (ptr != nullptr) {
			isOver = false;
			break;
		}
	}

	for (const auto& ptr : m_middlelineEnemies) {
		if (ptr != nullptr) {
			isOver = false;
			break;
		}
	}

	for (const auto& ptr : m_frontlineEnemies) {
		if (ptr != nullptr) {
			isOver = false;
			break;
		}
	}

	return isOver;
}