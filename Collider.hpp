#pragma once
#include <SFML/Graphics.hpp>
#include "CircleEntity.hpp"
#include <SFML/Audio.hpp>

class Collider {
public:
	static bool collided(const sf::Shape& first_obj, const sf::Shape& second_obj);
	static void handleBallCollisionByDirection(CircleEntity& vector);
	static bool collidedWithTopCorners(const sf::Shape& shape);
};