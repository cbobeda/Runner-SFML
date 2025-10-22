#pragma once

#include "Tile.h"


Tile::Tile(std::string filePath, float x, float y)
{
	if (!texture.loadFromFile(filePath))
	{
		std::cout << "Error while loading tile texture" << std::endl;
	}

	sprite = std::make_shared<sf::Sprite>(texture);
	sprite->setTexture(texture);
	sprite->setScale(sf::Vector2f(0.5f, 0.1f));
	sprite->setPosition(sf::Vector2f(x, y));
}

void Tile::update(float deltaTime, float speed)
{
	sprite->move(sf::Vector2f(-speed * deltaTime,0));
}

void Tile::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}

std::shared_ptr<sf::Sprite> Tile::getSprite()
{
	return sprite;
}