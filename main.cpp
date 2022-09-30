#include <iostream>
#include <SFML/Graphics.hpp>
#include "CircleEntity.hpp"
#include "RectangleEntity.hpp"
#include <cmath>

static const int WINDOW_HEIGHT = 400;
static const int WINDOW_WIDTH = 600;
static const float BALL_RADIUS = 10.0f;

const float PI = 3.1415f;

//float Lerp(const float firstFloat, const float secondFloat, const float by) {
//	return firstFloat + (secondFloat - firstFloat) * by;
//}
//
//sf::Vector2f Lerp(const sf::Vector2f& a, const sf::Vector2f& b, const float by) {
//	float retX = Lerp(a.x, b.x, by);
//	float retY = Lerp(a.y, b.y, by);
//	return sf::Vector2f(retX, retY);
//}

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

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32U), "Breakout Clone");

	RectangleEntity player_entity(sf::Vector2f(WINDOW_WIDTH / 4, 10), sf::Vector2f(0, WINDOW_HEIGHT - 20));

	CircleEntity ball(BALL_RADIUS, sf::Vector2f((WINDOW_WIDTH / 2) - BALL_RADIUS, (WINDOW_HEIGHT / 2) - BALL_RADIUS));

	ball.m_shape.setFillColor(sf::Color::White);
	ball.m_shape.setRadius(BALL_RADIUS);
	ball.m_shape.setOrigin(BALL_RADIUS, BALL_RADIUS);

	RectangleEntity rightWall(sf::Vector2f(1, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH - 1, 1));
	rightWall.m_shape.setFillColor(sf::Color::White);
	rightWall.m_direction = sf::Vector2f(0, 1);
	
	RectangleEntity leftWall(sf::Vector2f(1, WINDOW_HEIGHT), sf::Vector2f(0, 0));
	leftWall.m_direction = sf::Vector2f(0, 1);

	RectangleEntity ceiling(sf::Vector2f(WINDOW_WIDTH, 1), sf::Vector2f(0, 0));
	ceiling.m_direction = sf::Vector2f(1, 0);
	ceiling.m_shape.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			// TODO: Lerp
			if (event.key.code == sf::Keyboard::Key::Left) {
				player_entity.m_direction.x = -1;
				player_entity.m_shape.move(player_entity.getVelocity());
			}
			else if (event.key.code == sf::Keyboard::Key::Right) {
				player_entity.m_direction.x = 1;
				player_entity.m_shape.move(player_entity.getVelocity());
			}

			if (event.key.code == sf::Keyboard::Key::Escape || event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (collided(ball.m_shape, rightWall.m_shape)) {
			float angle = getAngleBetweenTwoVectors(ball.m_direction, rightWall.m_direction);
			std::cout << "Resulting angle from collision: " << angle << std::endl;
			ball.m_direction = getNormalizedVectorFromDirection(angle);
		}
		
		if (collided(ball.m_shape, leftWall.m_shape)) {
			float angle = getAngleBetweenTwoVectors(ball.m_direction, leftWall.m_direction);
			std::cout << "Resulting angle from collision: " << angle << std::endl;
			ball.m_direction = getNormalizedVectorFromDirection(angle);
		}
		
		if (collided(ball.m_shape, player_entity.m_shape)) {
			float angle = getAngleBetweenTwoVectors(ball.m_direction, player_entity.m_direction);
			std::cout << "Resulting angle from collision: " << angle << std::endl;
			ball.m_direction = getNormalizedVectorFromDirection(angle);
		}
		
		if (collided(ball.m_shape, ceiling.m_shape)) {
			float angle = getAngleBetweenTwoVectors(ball.m_direction, ceiling.m_direction);
			std::cout << "Resulting angle from collision: " << angle << std::endl;
			ball.m_direction = getNormalizedVectorFromDirection(angle);
		}

		ball.m_shape.move(ball.getVelocity());

		window.clear();

		window.draw(player_entity.m_shape);
		window.draw(ball.m_shape);
		//window.draw(rightWall.m_shape);
		//window.draw(leftWall.m_shape);
		//window.draw(ceiling.m_shape);

		window.display();
	}
}