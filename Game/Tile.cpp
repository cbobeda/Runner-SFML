#pragma once

#include "Tile.h"


Tile::Tile(std::shared_ptr<sf::Texture> texture, float x, float y)
{
	sprite = std::make_shared<sf::Sprite>(*texture);
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

std::shared_ptr<sf::Sprite> Tile::getSprite() const
{
	return sprite;
}