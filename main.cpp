#include <iostream>
#include <SFML/Graphics.hpp>
#include "CircleEntity.hpp"
#include "RectangleEntity.hpp"
#include <cmath>
#include <windows.h>
#include <profileapi.h>

static const int WINDOW_HEIGHT = 400;
static const int WINDOW_WIDTH = 600;
static const float BALL_SIZE = 10.0f;
static const float PI = 3.1415f;

float getMagnitude(const sf::Vector2f& a) {
	return sqrt((a.x * a.x) + (a.y * a.y));
}

float getAngleBetweenTwoVectors(const sf::Vector2f& a, const sf::Vector2f& b) {
	float a_mag = getMagnitude(a);
	float b_mag = getMagnitude(b);

	float times = (a.x * b.x) + (a.y * b.y);

	return (acos(times / (a_mag * b_mag)) * 180) / PI;
}

sf::Vector2f getNormalizedVectorFromDirection(const float angle) {
	return sf::Vector2f(cos(angle), sin(angle));
}

bool collided(const sf::Shape& first_obj, const sf::Shape& second_obj) {
	return first_obj.getGlobalBounds().intersects(second_obj.getGlobalBounds());
}

std::ostream& operator<<(std::ostream& stream, sf::Vector2f& vect) {
	return stream << "x: " << vect.x << ", y: " << vect.y << std::endl;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32U), "Breakout Clone");

	RectangleEntity player_entity(sf::Vector2f(WINDOW_WIDTH / 4, 10), sf::Vector2f((WINDOW_WIDTH / 2) - 10, WINDOW_HEIGHT - 20));

	RectangleEntity ball(sf::Vector2f(BALL_SIZE, BALL_SIZE), sf::Vector2f((WINDOW_WIDTH / 2) - BALL_SIZE, (WINDOW_HEIGHT / 2) - BALL_SIZE));

	ball.m_shape.setFillColor(sf::Color::Red);
	ball.m_shape.setOrigin(BALL_SIZE, BALL_SIZE);
	ball.m_speed = 0.2f;
	ball.m_direction.x = -1;

	RectangleEntity rightWall(sf::Vector2f(1, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH - 1, 1));
	rightWall.m_shape.setFillColor(sf::Color::White);
	rightWall.m_direction = sf::Vector2f(0, 1);
	
	RectangleEntity leftWall(sf::Vector2f(1, WINDOW_HEIGHT), sf::Vector2f(0, 0));
	leftWall.m_direction = sf::Vector2f(0, 1);

	RectangleEntity ceiling(sf::Vector2f(WINDOW_WIDTH, 1), sf::Vector2f(0, 0));
	ceiling.m_direction = sf::Vector2f(1, 0);
	ceiling.m_shape.setFillColor(sf::Color::White);

	sf::Vector2f last_position_for_backtracking = ball.m_shape.getPosition();

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.key.code == sf::Keyboard::Key::Left) {
				player_entity.m_direction.x = -1;
				player_entity.m_shape.move(sf::Vector2f(player_entity.m_direction.x * player_entity.m_speed, 0));
			}
			
			if (event.key.code == sf::Keyboard::Key::Right) {
				player_entity.m_direction.x = 1;
				player_entity.m_shape.move(sf::Vector2f(player_entity.m_direction.x * player_entity.m_speed, 0));
			}

			if (event.key.code == sf::Keyboard::Key::Escape || event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (collided(ball.m_shape, rightWall.m_shape)) {
			float angle = getAngleBetweenTwoVectors(ball.m_direction, rightWall.m_direction);
			ball.m_direction = getNormalizedVectorFromDirection(angle);
			ball.m_shape.setPosition(last_position_for_backtracking);
		} else if (collided(ball.m_shape, leftWall.m_shape)) {
			float angle = getAngleBetweenTwoVectors(ball.m_direction, leftWall.m_direction);
			ball.m_direction = getNormalizedVectorFromDirection(angle);
			ball.m_shape.setPosition(last_position_for_backtracking);
		} else if (collided(ball.m_shape, player_entity.m_shape)) {
			float angle = getAngleBetweenTwoVectors(ball.m_direction, player_entity.m_direction);
			ball.m_direction = getNormalizedVectorFromDirection(angle);
			ball.m_shape.setPosition(last_position_for_backtracking);
		} else if (collided(ball.m_shape, ceiling.m_shape)) {
			float angle = getAngleBetweenTwoVectors(ball.m_direction, ceiling.m_direction);
			ball.m_direction = getNormalizedVectorFromDirection(angle);
			ball.m_shape.setPosition(last_position_for_backtracking);
		}

		std::cout << ball.m_direction;

		ball.m_shape.move(ball.getVelocity());

		last_position_for_backtracking = ball.m_shape.getPosition();

		window.clear();

		window.draw(player_entity.m_shape);
		window.draw(ball.m_shape);
		window.draw(rightWall.m_shape);
		window.draw(leftWall.m_shape);
		window.draw(ceiling.m_shape);

		window.display();
	}
}