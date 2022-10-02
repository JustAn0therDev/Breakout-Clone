#include "Geometry.hpp"
#include <SFML/Graphics.hpp>

sf::Vector2f Geometry::getRotatedBy90Degrees(const sf::Vector2f& vector) {
	return sf::Vector2f(vector.y, vector.x * -1);
}