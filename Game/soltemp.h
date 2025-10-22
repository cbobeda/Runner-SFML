#pragma once
#include <SFML/Graphics.hpp>

class soltemp
{

public:
	soltemp(float x, float y);
	~soltemp();
	void update(sf::RenderWindow& window);
	sf::RectangleShape hitbox;
	sf::FloatRect getBounds() const;

private:
	float x;
	float y;
};
