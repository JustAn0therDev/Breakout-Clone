#include <iostream>
#include <SFML/Graphics.hpp>
#include "CircleEntity.hpp"

static const int WINDOW_HEIGHT = 400;
static const int WINDOW_WIDTH = 600;

bool Collided(const sf::Shape& obj, const sf::Shape& anotherObj) {
	return obj.getGlobalBounds().intersects(anotherObj.getGlobalBounds());
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32U), "Breakout Clone");
	window.setFramerateLimit(60);

	CircleEntity ball(sf::Vector2f((WINDOW_WIDTH / 2) - 20.0f, (WINDOW_HEIGHT / 2) - 20.0f));

	sf::RectangleShape rightWall;
	sf::RectangleShape leftWall;

	rightWall.setFillColor(sf::Color::White);
	rightWall.setSize(sf::Vector2f(1, WINDOW_HEIGHT));

	leftWall.setFillColor(sf::Color::White);
	leftWall.setSize(sf::Vector2f(1, WINDOW_HEIGHT));

	rightWall.setPosition(sf::Vector2f(WINDOW_WIDTH, 0));
	leftWall.setPosition(sf::Vector2f(-1, 0));

	ball.m_shape.setFillColor(sf::Color::White);

	ball.m_shape.setRadius(20.0f);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.key.code == sf::Keyboard::Key::Escape || event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ball.m_shape.move(ball.getMoveOffset());

		if (Collided(ball.m_shape, rightWall)) {
			ball.m_direction = sf::Vector2f(-1, 0);
		}
		else if (Collided(ball.m_shape, leftWall)) {
			ball.m_direction = sf::Vector2f(1, 0);
		}

		window.clear();

		window.draw(ball.m_shape);
		
		window.draw(rightWall);
		window.draw(leftWall);

		window.display();
	}
}