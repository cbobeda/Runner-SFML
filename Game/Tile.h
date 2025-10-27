#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Tile
{
	public:

		Tile(std::shared_ptr<sf::Texture> texture, float x, float y);
		void update(float deltaTime, float speed);
		void draw(sf::RenderWindow& window);
		std::shared_ptr<sf::Sprite> getSprite() const;
		sf::FloatRect getBounds() const {return sprite.get()->getGlobalBounds();}

	private:
		std::shared_ptr<sf::Sprite> sprite;


};

