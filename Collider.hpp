#pragma once
#include <SFML/Graphics.hpp>

class Collider {
public:
	static bool collided(const sf::Shape& first_obj, const sf::Shape& second_obj);
};