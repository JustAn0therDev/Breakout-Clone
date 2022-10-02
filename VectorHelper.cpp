#include <SFML/Graphics.hpp>
#include "Geometry.hpp"

class VectorHelper {
	friend std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vector) {
		return stream << vector.x << ", " << vector.y;
	}
};