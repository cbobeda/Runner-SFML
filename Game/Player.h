#pragma once
#include <SFML/Graphics.hpp>
#include "TileManager.h"

class Player
{
public:
	Player();
	~Player();
	float getx();
	float gety();
	void update(sf::RenderWindow& window, float deltaTim, const std::vector<Tile>& tileVector);
	
private:

	void dash(); 
	void jump(float deltaTime);
	void gravity(float deltaTim);
	void fixheigh();

	float x = 100.f;
	float y = 50.f;
	float speed = 1.f;
	bool jumping = false;
	bool onground = false;
	
	sf::Vector2f velocity;
	float gravityStrength = 1000.f;
	float jumpStrength = -400.f;
	float maxFallSpeed = 800.f;

	sf::FloatRect getBounds() const;
	bool collidesWith(const sf::FloatRect& rect) const;
	const Tile* getCollidingTile(const std::vector<Tile>& tileVector) const;


	sf::RectangleShape hitbox;
	void controle(int input, float deltaTime);

};
