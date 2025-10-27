#include "Coins.h"

Coins::Coins(std::shared_ptr<sf::Texture> texture, float x, float y)
{
	sprite = std::make_shared<sf::Sprite>(*texture);
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