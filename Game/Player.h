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

	float x = 50.f;
	float y = 50.f;
	float speed = 1.f;
	sf::Time timejump;
	bool jumping = false;
	bool onground = true;

	sf::RectangleShape hitbox;
	void controle(int input);

};

Player::Player()
{
}

Player::~Player()
{
}

