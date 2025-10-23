#include "Coins.h"

Coins::Coins(std::string filePath, float x, float y) : cointexture(std::make_shared<sf::Texture>())
{
	if (!cointexture->loadFromFile(filePath))
	{
		std::cout << "Error while loading tile texture" << std::endl;
	}
	sprite = std::make_shared<sf::Sprite>(*cointexture);
	sprite->setScale(sf::Vector2f(0.05f, 0.05f));
	sprite->setPosition(sf::Vector2f(x, y));
}

void Coins::update(float deltaTime, float speed)
{
	sprite->move(sf::Vector2f(-speed * deltaTime, 0));
}

void Coins::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}

std::shared_ptr<sf::Sprite> Coins::getSprite()
{
	return sprite;
}