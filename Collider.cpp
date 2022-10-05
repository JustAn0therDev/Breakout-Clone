#include "Collider.hpp"
#include "SFML/Graphics.hpp"
#include "Geometry.hpp"
#include "CircleEntity.hpp"
#include "Constants.hpp"

bool Collider::collided(const sf::Shape& first_obj, const sf::Shape& second_obj) {
	return first_obj.getGlobalBounds().intersects(second_obj.getGlobalBounds());
}

void Collider::handleBallCollisionByDirection(CircleEntity& ball) {
	ball.m_direction = (ball.m_direction.y > 0 && ball.m_direction.x > 0) || (ball.m_direction.y < 0 && ball.m_direction.x < 0) ?
		Geometry::getRotatedBy90DegreesClockwise(ball.m_direction) :
		Geometry::getRotatedBy90DegreesCounterClockwise(ball.m_direction);
}

bool Collider::collidedWithTopCorners(const sf::Shape& shape) {
	sf::FloatRect globalBounds = shape.getGlobalBounds();
	sf::Vector2f pos = shape.getPosition();

	sf::Vector2f totalPos = sf::Vector2f(pos.x + (globalBounds.width / 2.0f), pos.y + (globalBounds.height / 2.0f));

	return (totalPos.x == 0 && totalPos.y == 0) || (totalPos.x == WINDOW_WIDTH && totalPos.y == 0);
}