#include <iostream>
#include <SFML/Graphics.hpp>
#include "CircleEntity.hpp"
#include "RectangleEntity.hpp"
#include <cmath>
#include "Geometry.hpp"
#include "Enemy.hpp"
#include "EnemyType.hpp"
#include "VectorHelper.hpp"

static const int WINDOW_HEIGHT = 400;
static const int WINDOW_WIDTH = 600;
static const float BALL_RADIUS = 10.0f;

std::vector<Enemy*> makeEnemies(const EnemyType enemy_type, const float amount, const float y_pos) {
	std::vector<Enemy*> enemies;
	enemies.reserve(static_cast<int>(amount));

	float size = (WINDOW_WIDTH / amount) - 10 * 2;

	float space_between = (WINDOW_WIDTH - (size * amount)) / (amount + 1);

	float pos = space_between;

	for (int i = 0; i < static_cast<int>(amount); i++) {
		enemies.emplace_back(new Enemy(enemy_type, sf::Vector2f(size, 10), sf::Vector2f(pos, y_pos)));
		pos += size + space_between;
	}

	return enemies;
}

bool collided(const sf::Shape& first_obj, const sf::Shape& second_obj) {
	return first_obj.getGlobalBounds().intersects(second_obj.getGlobalBounds());
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32U), "Breakout Clone");

	RectangleEntity player_entity(sf::Vector2f(WINDOW_WIDTH / 4, 10), sf::Vector2f((WINDOW_WIDTH / 2) - 10, WINDOW_HEIGHT - 20), sf::Color::Magenta);

	CircleEntity ball(BALL_RADIUS, sf::Vector2f((WINDOW_WIDTH / 2) - BALL_RADIUS, (WINDOW_HEIGHT / 2) - BALL_RADIUS));
	ball.m_shape.setFillColor(sf::Color::Blue);

	RectangleEntity right_wall(sf::Vector2f(1, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH - 1, 1), sf::Color::White);

	RectangleEntity left_wall(sf::Vector2f(1, WINDOW_HEIGHT), sf::Vector2f(0, 0), sf::Color::White);

	RectangleEntity ceiling(sf::Vector2f(WINDOW_WIDTH, 1), sf::Vector2f(0, 0), sf::Color::White);

	std::vector<Enemy*> enemies = makeEnemies(EnemyType::Strong, 5, 50);
	std::vector<Enemy*> middleline_enemies = makeEnemies(EnemyType::Normal, 5, 70);
	std::vector<Enemy*> frontline_enemies = makeEnemies(EnemyType::Weak, 10, 90);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.key.code == sf::Keyboard::Key::Left) {
				player_entity.m_direction.x = -1;

				if (player_entity.m_shape.getPosition().x > 0) {
					player_entity.m_shape.move(player_entity.m_direction.x * player_entity.m_speed, 0);
				}
			}

			if (event.key.code == sf::Keyboard::Key::Right) {
				player_entity.m_direction.x = 1;
				
				float total_movement = player_entity.m_shape.getPosition().x + player_entity.m_shape.getSize().x;

				if (total_movement < WINDOW_WIDTH) {
					player_entity.m_shape.move(player_entity.m_direction.x * player_entity.m_speed, 0);
				}
			}

			if (event.key.code == sf::Keyboard::Key::Escape || event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (collided(ball.m_shape, left_wall.m_shape) ||
			collided(ball.m_shape, ceiling.m_shape) ||
			collided(ball.m_shape, right_wall.m_shape) || 
			collided(ball.m_shape, player_entity.m_shape)) {
			ball.m_direction = Geometry::getRotatedBy90DegreesClockwise(ball.m_direction);
		}

		for (auto& enemy : enemies) {
			if (enemy != nullptr && collided(ball.m_shape, enemy->m_rectangle_entity.m_shape)) {
				enemy->takeDamage();
				
				if (enemy->m_health == 0) {
					delete enemy;
					enemy = nullptr;
				}

				// Backtracking after collision.
				ball.m_shape.move(Geometry::getRotatedBy180Degrees(ball.m_direction));
				ball.m_direction = Geometry::getRotatedBy90DegreesClockwise(ball.m_direction);
			}
		}

		for (auto& enemy : middleline_enemies) {
			if (enemy != nullptr && collided(ball.m_shape, enemy->m_rectangle_entity.m_shape)) {
				enemy->takeDamage();
				
				if (enemy->m_health == 0) {
					delete enemy;
					enemy = nullptr;
				}

				// Backtracking after collision.
				ball.m_shape.move(Geometry::getRotatedBy180Degrees(ball.m_direction));
				ball.m_direction = Geometry::getRotatedBy90DegreesClockwise(ball.m_direction);
			}
		}

		for (auto& enemy : frontline_enemies) {
			if (enemy != nullptr && collided(ball.m_shape, enemy->m_rectangle_entity.m_shape)) {
				enemy->takeDamage();

				if (enemy->m_health == 0) {
					delete enemy;
					enemy = nullptr;
				}

				// Backtracking after collision.
				ball.m_shape.move(Geometry::getRotatedBy180Degrees(ball.m_direction));
				ball.m_direction = Geometry::getRotatedBy90DegreesClockwise(ball.m_direction);
			}
		}

		ball.m_shape.move(ball.getVelocity());

		window.clear();

		window.draw(player_entity.m_shape);
		window.draw(ball.m_shape);

		for (const auto& enemy : enemies) {
			if (enemy != nullptr) {
				window.draw(enemy->m_rectangle_entity.m_shape);
			}
		}

		for (const auto& enemy : middleline_enemies) {
			if (enemy != nullptr) {
				window.draw(enemy->m_rectangle_entity.m_shape);
			}
		}

		for (const auto& enemy : frontline_enemies) {
			if (enemy != nullptr) {
				window.draw(enemy->m_rectangle_entity.m_shape);
			}
		}

		window.display();
	}
}