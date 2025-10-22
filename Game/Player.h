#pragma once
#include <SFML/Graphics.hpp>
#include "soltemp.h"

class Player
{
public:
	Player();
	~Player();
	float getx();
	float gety();
	void update(sf::RenderWindow& window, std::vector<soltemp> sol);
	
private:

	void dash(); 
	void jump();
	void gravity();

	float x = 50.f;
	float y = 50.f;
	float speed = 1.f;
	sf::Time timejump;
	bool jumping = false;
	bool onground = false;
	sf::FloatRect getBounds() const;
	bool collidesWith(const sf::FloatRect& rect) const;
	sf::RectangleShape hitbox;
	void controle(int input);

};
