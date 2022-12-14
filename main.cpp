#include <iostream>
#include <SFML/Graphics.hpp>
#include "CircleEntity.hpp"
#include "RectangleEntity.hpp"
#include <cmath>
#include "Geometry.hpp"
#include "Enemy.hpp"
#include "EnemyType.hpp"
#include "VectorHelper.hpp"
#include "Constants.hpp"
#include "Game.hpp"
#include "Collider.hpp"
#include <Windows.h>
#include <SFML/Audio.hpp>
#include "AudioHandler.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32U), "Breakout Clone");
	window.setFramerateLimit(60);

	SetForegroundWindow(window.getSystemHandle());
	ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);

	sf::Font font;

	if (!font.loadFromFile("Assets/Fonts/PressStart2P-Regular.ttf")) {
		std::cout << "Could not load font from file." << std::endl;
		exit(1);
	}

	Game* game = new Game(font);
	AudioHandler audioHandler;

	game->m_playerEntity.m_direction = sf::Vector2f(0, 0);

	while (window.isOpen()) {
		sf::Event event;
		game->m_playerEntity.m_direction.x = 0;

		while (window.pollEvent(event)) {
			if (event.key.code == sf::Keyboard::Key::Escape || event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			if (game->m_playerEntity.m_shape.getPosition().x > -(game->m_playerEntity.m_shape.getGlobalBounds().width / 2.0f)) {
				game->m_playerEntity.m_direction.x = -1;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			if (game->m_playerEntity.m_shape.getPosition().x + (game->m_playerEntity.m_shape.getGlobalBounds().width / 2.0f) < WINDOW_WIDTH) {
				game->m_playerEntity.m_direction.x = 1;
			}
		}

		game->m_playerEntity.m_shape.move(game->m_playerEntity.m_speed * game->m_playerEntity.m_direction.x, 0);

		if (Collider::collidedWithTopCorners(game->m_ball.m_shape)) {
			audioHandler.playBoop();
			game->m_ball.m_direction = Geometry::getRotatedBy180Degrees(game->m_ball.m_direction);
		}

		if (Collider::collided(game->m_ball.m_shape, game->m_ceiling.m_shape)) {
			audioHandler.playBoop();
			game->m_ball.m_direction = game->m_ball.m_direction.x > 0 ? Geometry::getRotatedBy90DegreesCounterClockwise(game->m_ball.m_direction) :
				Geometry::getRotatedBy90DegreesClockwise(game->m_ball.m_direction);
		}
		else if (Collider::collided(game->m_ball.m_shape, game->m_leftWall.m_shape)) {
			audioHandler.playBoop();
			game->m_ball.m_direction = game->m_ball.m_direction.y > 0 ? Geometry::getRotatedBy90DegreesClockwise(game->m_ball.m_direction) :
				Geometry::getRotatedBy90DegreesCounterClockwise(game->m_ball.m_direction);
		}
		else if (Collider::collided(game->m_ball.m_shape, game->m_rightWall.m_shape)) {
			audioHandler.playBoop();
			game->m_ball.m_direction = game->m_ball.m_direction.y > 0 ? Geometry::getRotatedBy90DegreesCounterClockwise(game->m_ball.m_direction) :
				Geometry::getRotatedBy90DegreesClockwise(game->m_ball.m_direction);
		}
		else if (Collider::collided(game->m_ball.m_shape, game->m_playerEntity.m_shape)) {
			audioHandler.playBoop();
			sf::Vector2f playerPos = game->m_playerEntity.m_shape.getPosition();
			sf::Vector2f ballPos = game->m_ball.m_shape.getPosition();

			float totalPlayerPosWithGlobalBounds = playerPos.x + (game->m_playerEntity.m_shape.getGlobalBounds().width / 2.0f);
			float totalBallPosWithGlobalBounds = ballPos.x + (game->m_ball.m_shape.getGlobalBounds().width / 2.0f);

			if (totalBallPosWithGlobalBounds >= totalPlayerPosWithGlobalBounds && game->m_ball.m_direction.x < 0 ||
				(totalBallPosWithGlobalBounds >= totalPlayerPosWithGlobalBounds && game->m_ball.m_direction.x > 0)) {
				game->m_ball.m_direction = Geometry::getRotatedBy90DegreesClockwise(game->m_ball.m_direction);
			}
			else if (totalBallPosWithGlobalBounds <= totalPlayerPosWithGlobalBounds && game->m_ball.m_direction.x < 0 ||
				(totalBallPosWithGlobalBounds <= totalPlayerPosWithGlobalBounds && game->m_ball.m_direction.x > 0)) {
				game->m_ball.m_direction = Geometry::getRotatedBy90DegreesCounterClockwise(game->m_ball.m_direction);
			}

			if ((game->m_ball.m_direction.x == -0.5f && game->m_ball.m_direction.y == 0.5f) ||
				(game->m_ball.m_direction.x == 0.5f && game->m_ball.m_direction.y == 0.5f)) {
				Collider::handleBallCollisionByDirection(game->m_ball);
			}
		}

		for (auto& enemy : game->m_backlineEnemies) {
			if (enemy != nullptr && Collider::collided(game->m_ball.m_shape, enemy->m_rectangle_entity.m_shape)) {
				enemy->takeDamage();

				if (enemy->m_health == 0) {
					audioHandler.playBubblePop();
					delete enemy;
					enemy = nullptr;
					Collider::handleBallCollisionByDirection(game->m_ball);
					break;
				}

				audioHandler.playThonk();
				Collider::handleBallCollisionByDirection(game->m_ball);
			}
		}

		for (auto& enemy : game->m_middlelineEnemies) {
			if (enemy != nullptr && Collider::collided(game->m_ball.m_shape, enemy->m_rectangle_entity.m_shape)) {
				enemy->takeDamage();

				if (enemy->m_health == 0) {
					audioHandler.playBubblePop();
					delete enemy;
					enemy = nullptr;
					Collider::handleBallCollisionByDirection(game->m_ball);
					break;
				}

				audioHandler.playThonk();
				Collider::handleBallCollisionByDirection(game->m_ball);
			}
		}

		for (auto& enemy : game->m_frontlineEnemies) {
			if (enemy != nullptr && Collider::collided(game->m_ball.m_shape, enemy->m_rectangle_entity.m_shape)) {
				enemy->takeDamage();

				if (enemy->m_health == 0) {
					audioHandler.playBubblePop();
					delete enemy;
					enemy = nullptr;
					Collider::handleBallCollisionByDirection(game->m_ball);
					break;
				}

				audioHandler.playThonk();
				Collider::handleBallCollisionByDirection(game->m_ball);
			}
		}

		game->m_ball.m_shape.move(game->m_ball.getVelocity());

		if (game->ballIsOutOfBounds()) {
			delete game;
			game = new Game(font);
			game->m_textColor.a = 255;
		}

		if (game->m_textColor.a > 0) {
			game->m_textColor.a -= 5;
			game->m_restartText.setFillColor(game->m_textColor);
		}

		window.clear();

		window.draw(game->m_ball.m_shape);
		window.draw(game->m_playerEntity.m_shape);
		window.draw(game->m_restartText);

		for (const auto& enemy : game->m_backlineEnemies) {
			if (enemy != nullptr) {
				window.draw(enemy->m_rectangle_entity.m_shape);
			}
		}

		for (const auto& enemy : game->m_middlelineEnemies) {
			if (enemy != nullptr) {
				window.draw(enemy->m_rectangle_entity.m_shape);
			}
		}

		for (const auto& enemy : game->m_frontlineEnemies) {
			if (enemy != nullptr) {
				window.draw(enemy->m_rectangle_entity.m_shape);
			}
		}

		if (game->isOver()) {
			audioHandler.playGameOverTheme();
			window.draw(game->m_gameOverText);
			window.display();
			while (window.waitEvent(event)) {
				if (event.key.code == sf::Keyboard::Key::Enter || event.type == sf::Event::Closed) {
					window.close();
					break;
				}
				continue;
			}
		}

		window.display();
	}
}