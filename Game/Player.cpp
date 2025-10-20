#include "Player.h"
#include<vector>
Player::Player(){}

float Player::getx() { return x;}
float Player::gety() { return y;}

void Player::dash(){
	return;
//augmenter la speed total

}
void Player::jump() {
	if (onground) {
		onground = false;
		jumping = true;
		//monter le y pendant un temps et passer onground a false puis 

	}
} 


void Player::controle(int input) {
	if (input == 1)
	{
		jump();
	}
	else if (input == 2) {
		dash();
	}
	else{
		return;
	}
}

void Player::gravity() {
	if (true)//!(player collide sol)
	{
		if (!jumping) {
			y -= 1;
		}
	}
	else { onground = true;}

};


void Player::update(){
	if (sf::Mouse::isButtonPressed)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			controle(1);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			controle(2);
	}
	//si perso contact avec le sol onground = true
}

