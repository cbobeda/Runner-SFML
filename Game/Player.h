#pragma once
#include <SFML/Graphics.hpp>
#include "TileManager.h"
#include "Coins.h"

class Player
{
public:
	Player();
	~Player();
	float getx();
	float gety();
	void update(sf::RenderWindow& window, float deltaTime, std::vector<Tile>& tileVector, const std::vector<Tile>& consttileVector, std::vector<Coins>& coinVector, const std::vector<Coins>& constcoinVector);
	
private:

	void dash(std::vector<Tile>& tileVector, std::vector<Coins>& coinVector);
	void jump(float deltaTime);
	void gravity(float deltaTim);

	float x = 100.f;
	float y = 50.f;
	float speed = 1.f;
	bool jumping = false;
	bool onground = false;
	bool alive = true;

	sf::Vector2f velocity;
	float gravityStrength = 1000.f;
	float jumpStrength = -400.f;
	float maxFallSpeed = 800.f;

	sf::FloatRect getBounds() const;
	bool collidesWith(const sf::FloatRect& rect) const;
	const Tile* getCollidingTile(const std::vector<Tile>& tileVector) const;


	sf::RectangleShape hitbox;
	void controle(int input, float deltaTime, std::vector<Tile>& tileVector, std::vector<Coins>& coinVector);

};
