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
	void update(sf::RenderWindow& window, float deltaTim, std::vector<Tile>& tileVector);
	
private:

	void dash(); 
	void jump(float deltaTime);
	void gravity(float deltaTim);
	float velocity;
	float speed;

	float x = 50.f;
	float y = 50.f;
	float speed = 1.f;
	bool jumping = false;
	bool onground = false;
	
	sf::FloatRect getBounds() const;
	bool collidesWith(const sf::FloatRect& rect) const;
	bool collidesGround(const std::vector<Tile>& tileVector) const;


	sf::RectangleShape hitbox;
	void controle(int input, float deltaTime);

};
