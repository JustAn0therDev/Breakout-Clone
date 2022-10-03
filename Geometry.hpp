#pragma once
#include <SFML/Graphics.hpp>

class Geometry {
public:
	static sf::Vector2f getRotatedBy90DegreesClockwise(const sf::Vector2f& vector);
	static sf::Vector2f getRotatedBy180Degrees(const sf::Vector2f& vector);
};