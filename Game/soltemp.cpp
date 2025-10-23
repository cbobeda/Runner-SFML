#include "soltemp.h"

soltemp::soltemp(float x, float y) : x(x), y(y) {

	hitbox = sf::RectangleShape({ 20, 10 });
	hitbox.setFillColor(sf::Color::Blue);
	hitbox.setPosition({ x, y });
}

soltemp::~soltemp()
{
}

sf::FloatRect soltemp::getBounds() const { return hitbox.getGlobalBounds(); }

void soltemp::update(sf::RenderWindow& window) {
	window.draw(hitbox);
}