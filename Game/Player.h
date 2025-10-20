#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	float getx();
	float gety();
	void update();
	
private:

	void dash(); 
	void jump();
	void gravity();

	float x;
	float y;
	float speed;
	bool jumping;

	sf::RectangleShape hitbox;
	void controle(int input);

};

Player::Player()
{
}

Player::~Player()
{
}

