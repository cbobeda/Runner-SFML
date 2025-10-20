#include "Player.h"
#include<vector>

sf::FloatRect box::getBounds() const { return hitbox.getGlobalBounds(); }


Player::Player(){
	hitbox = sf::RectangleShape({ 50, 50 });
	hitbox.setPosition({ x, y });

}

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
sf::FloatRect Player::getBounds() const {
	return hitbox.getGlobalBounds();
}

bool Player::collidesWith(const sf::FloatRect& rect) const {
	const auto A = getBounds();
	return (A.position.x < rect.position.x + rect.size.x) &&
		(A.position.x + A.size.x > rect.position.x) &&
		(A.position.y < rect.position.y + rect.size.y) &&
		(A.position.y + A.size.y > rect.position.y);
}

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



