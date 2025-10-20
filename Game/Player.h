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
	box boxs[1];
	sf::FloatRect getBounds() const;
	bool collidesWith(const sf::FloatRect& rect) const;
	sf::RectangleShape hitbox;
	void controle(int input);

};

Player::Player()
{
}

Player::~Player()
{
}



//temporaire =====================================================================================================================================================

class box
{
public:
	box();
	~box();
	sf::RectangleShape hitbox;

private:
	sf::FloatRect getBounds() const;
};

box::box()
{
}

box::~box()
{
}