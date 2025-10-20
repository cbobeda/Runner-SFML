#include "Player.h"
#include<vector>
Player::Player(){
	x = 50.f;
	y = 50.f;
	speed = 1;
	jumping = false;
}

float Player::getx() { return x;}
float Player::gety() { return y;}

void Player::dash(){

//augmenter la speed total

}
void Player::jump() {

	//monter le y pendant un temps et passer jumping a true puis 
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

	//descendre si pas en etat jump et si pas en collision avec le sol

};


void Player::update(){
	if (sf::Mouse::isButtonPressed)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			controle(1);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			controle(2);
	}
	//si perso contact avec le sol jumping = true
}

