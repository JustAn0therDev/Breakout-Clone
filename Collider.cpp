#include "Collider.hpp"
#include "SFML/Graphics.hpp"
#include "Geometry.hpp"
#include "CircleEntity.hpp"

bool Collider::collided(const sf::Shape& first_obj, const sf::Shape& second_obj) {
	return first_obj.getGlobalBounds().intersects(second_obj.getGlobalBounds());
}

void Collider::handleBallCollisionByDirection(CircleEntity& ball) {
	ball.m_direction = (ball.m_direction.y > 0 && ball.m_direction.x > 0) || (ball.m_direction.y < 0 && ball.m_direction.x < 0) ?
		Geometry::getRotatedBy90DegreesClockwise(ball.m_direction) :
		Geometry::getRotatedBy90DegreesCounterClockwise(ball.m_direction);
}