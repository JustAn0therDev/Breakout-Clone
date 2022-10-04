#include "Geometry.hpp"
#include <SFML/Graphics.hpp>

sf::Vector2f Geometry::getRotatedBy90DegreesClockwise(const sf::Vector2f& vector) {
	return sf::Vector2f(vector.y, vector.x * -1);
}

sf::Vector2f Geometry::getRotatedBy90DegreesCounterClockwise(const sf::Vector2f& vector) {
	return sf::Vector2f(vector.y * -1, vector.x);
}