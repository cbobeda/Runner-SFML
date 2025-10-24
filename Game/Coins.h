#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

class Coins
{
	public:
		Coins(std::shared_ptr<sf::Texture> texture, float x, float y);
		void update(float deltaTime, float speed);
		void draw(sf::RenderWindow& window);
		std::shared_ptr<sf::Sprite> getSprite();
	private:
		std::shared_ptr<sf::Sprite> sprite;

};

