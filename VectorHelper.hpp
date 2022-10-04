#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class VectorHelper {
public:
	friend std::ostream& operator<<(std::ostream stream, const sf::Vector2f vector);
};