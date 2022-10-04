#include "Collider.hpp"
#include "SFML/Graphics.hpp"

bool Collider::collided(const sf::Shape& first_obj, const sf::Shape& second_obj) {
	return first_obj.getGlobalBounds().intersects(second_obj.getGlobalBounds());
}