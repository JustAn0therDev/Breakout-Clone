#include <iostream>
#include <SFML/Graphics.hpp>
#include "CircleEntity.hpp"
#include "RectangleEntity.hpp"
#include <cmath>
#include "Geometry.hpp"

static const int WINDOW_HEIGHT = 400;
static const int WINDOW_WIDTH = 600;
static const float BALL_RADIUS = 10.0f;
static const float PI = 3.1415f;

bool collided(const sf::Shape& first_obj, const sf::Shape& second_obj) {
	return first_obj.getGlobalBounds().intersects(second_obj.getGlobalBounds());
}

std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vector) {
	return std::cout << vector.x << ", " << vector.y;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32U), "Breakout Clone");

	RectangleEntity player_entity(sf::Vector2f(WINDOW_WIDTH / 4, 10), sf::Vector2f((WINDOW_WIDTH / 2) - 10, WINDOW_HEIGHT - 20));

	CircleEntity ball(BALL_RADIUS, sf::Vector2f((WINDOW_WIDTH / 2) - BALL_RADIUS, (WINDOW_HEIGHT / 2) - BALL_RADIUS));

	ball.m_shape.setFillColor(sf::Color::Red);

	RectangleEntity right_wall(sf::Vector2f(1, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH - 1, 1));
	right_wall.m_shape.setFillColor(sf::Color::White);
	
	RectangleEntity left_wall(sf::Vector2f(1, WINDOW_HEIGHT), sf::Vector2f(0, 0));
	left_wall.m_shape.setFillColor(sf::Color::White);

	RectangleEntity ceiling(sf::Vector2f(WINDOW_WIDTH, 1), sf::Vector2f(0, 0));
	ceiling.m_shape.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.key.code == sf::Keyboard::Key::Left) {
				player_entity.m_direction.x = -1;
				player_entity.m_shape.move(player_entity.m_direction.x * player_entity.m_speed, 0);
			}
			
			if (event.key.code == sf::Keyboard::Key::Right) {
				player_entity.m_direction.x = 1;
				player_entity.m_shape.move(player_entity.m_direction.x * player_entity.m_speed, 0);
			}

			if (event.key.code == sf::Keyboard::Key::Escape || event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (collided(ball.m_shape, right_wall.m_shape) || 
			collided(ball.m_shape, left_wall.m_shape) || 
			collided(ball.m_shape, player_entity.m_shape) ||
			collided(ball.m_shape, ceiling.m_shape)) {
			ball.m_direction = Geometry::getRotatedBy90Degrees(ball.m_direction);
		}

		ball.m_shape.move(ball.getVelocity());

		window.clear();

		window.draw(player_entity.m_shape);
		window.draw(ball.m_shape);

		window.display();
	}
}