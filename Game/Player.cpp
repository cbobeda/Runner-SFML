#include "Player.h"

#include<vector>

Player::Player(){
	hitbox = sf::RectangleShape({ 10, 10 });
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setPosition({ x, y });
}

Player::~Player()
{
}

float Player::getx() { return x;}
float Player::gety() { return y;}

void Player::dash(){
	return;
//augmenter la speed total

}

void Player::jump(float deltaTime) {
	if (y < 20)jumping = false;
	if (onground || jumping) {
		onground = false;
		jumping = true;
		y -= 100 * deltaTime;//monter le y pendant un temps et passer onground a false puis
	}
	 
} 


void Player::controle(int input, float deltaTime) {
	if (input == 1)
	{
		jump(deltaTime);
	}
	else if (input == 2) {
		dash();
	}
	else{
		return;
	}
}

void Player::gravity(float deltaTime) {
	const float gravitySpeed = 100.0f;

	if (!onground) {
		if (!jumping) {
			y += gravitySpeed * deltaTime;
		}
	}
}

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

void Player::update(sf::RenderWindow& window, float deltaTime, std::vector<soltemp> sol) {
	if(jumping)
		hitbox.setFillColor(sf::Color::Red);
	else
		hitbox.setFillColor(sf::Color::Green);

	for (auto& b : sol) {
		b.update(window);
		if (collidesWith(b.getBounds()))
		{
			onground = true;
			exit;
		}
	}
	gravity(deltaTime);
	if (sf::Mouse::isButtonPressed)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			controle(1, deltaTime);
		else
			jumping = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			controle(2, deltaTime);
	}
	hitbox.setPosition({ x, y });
	window.draw(hitbox);
}



