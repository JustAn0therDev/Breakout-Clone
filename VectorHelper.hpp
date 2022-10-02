#include <SFML/Graphics.hpp>
#include <iostream>

class VectorHelper {
public:
	static std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vector);
};