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
	void posReset();

public:
	bool alive = true;
	bool coin = false;

private:

	void dash(std::vector<Tile>& tileVector, std::vector<Coins>& coinVector, float deltaTime);
	void jump(float deltaTime);
	void gravity(float deltaTim);

	float x = 500.f;
	float y = 0.f;
	bool jumping = false;
	bool onground = false;
	bool candash = true;
	const float dashDistance = 360.f;

	sf::Clock dashClock;
	const float dashCooldown = 1.5f;

	sf::Vector2f velocity;
	float gravityStrength = 1000.f;
	float jumpStrength = -400.f;
	float maxFallSpeed = 800.f;

	sf::FloatRect getBounds() const;
	bool collidesWith(const sf::FloatRect& rect) const;
	const Tile* getCollidingTile(const std::vector<Tile>& tileVector) const;
	const Coins* getCollidingCoin(std::vector<Coins>& coinVector) const ;


	sf::RectangleShape hitbox;
	sf::RectangleShape shadow;
	void controle(int input, float deltaTime, std::vector<Tile>& tileVector, std::vector<Coins>& coinVector);

};
