#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Tile
{
	public:

		Tile(std::string filePath, float x, float y);
		void update(float deltaTime, float speed);
		void draw(sf::RenderWindow& window);
		std::shared_ptr<sf::Sprite> getSprite();

	private:
		std::shared_ptr <sf::Texture> texture;
		std::shared_ptr<sf::Sprite> sprite;


};

