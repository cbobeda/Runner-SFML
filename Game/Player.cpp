#include "Player.h"

#include<vector>

Player::Player(){
	hitbox = sf::RectangleShape({ 25, 25 });
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setPosition({ x, y });
}

Player::~Player()
{
}

float Player::getx() { return x;}
float Player::gety() { return y;}

void Player::dash(std::vector<Tile>& tileVector,std::vector<Coins>& coinVector){

	return;
	//augmenter la speed total

}

void Player::controle(int input, float deltaTime, std::vector<Tile>& tileVector, std::vector<Coins>& coinVector) {
	if (input == 1)
	{
		jump(deltaTime);
	}
	else if (input == 2) {
		dash(tileVector, coinVector);
	}
	else{
		return;
	}
}

void Player::gravity(float deltaTime) {
	if (!onground) {
		velocity.y += gravityStrength * deltaTime;

		if (velocity.y > maxFallSpeed)
			velocity.y = maxFallSpeed;
	}
}

void Player::jump(float deltaTime) {
	if (onground) {
		velocity.y = jumpStrength;
		onground = false;
		jumping = true;
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

const Tile* Player::getCollidingTile(const std::vector<Tile>& tileVector) const {
	for (const auto& tile : tileVector) {
		if (collidesWith(tile.getBounds())) {
			return &tile;
		}
	}
	return nullptr;
}


void Player::update(sf::RenderWindow& window, float deltaTime, std::vector<Tile>& tileVector, const std::vector<Tile>& consttileVector, std::vector<Coins>& coinVector, const std::vector<Coins>& constcoinVector) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		controle(1, deltaTime, tileVector, coinVector);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		controle(2, deltaTime, tileVector, coinVector);

	gravity(deltaTime);
	y += velocity.y * deltaTime;

	const Tile* collidedTile = getCollidingTile(consttileVector);
	if (collidedTile) {
		sf::FloatRect tileBounds = collidedTile->getBounds();
		sf::FloatRect playerBounds = getBounds();

		if (playerBounds.position.y + playerBounds.size.y > tileBounds.position.y && playerBounds.position.x <= tileBounds.position.x)
		{ 
			if (playerBounds.position.y + playerBounds.size.y - tileBounds.position.y > playerBounds.size.y / 2)
				alive = false;
		}


		else if (playerBounds.position.y + playerBounds.size.y > tileBounds.position.y && playerBounds.position.x > tileBounds.position.x ) {
			y = tileBounds.position.y - playerBounds.size.y;
			velocity.y = 0.f;
			onground = true;
			jumping = false;
		}

	}
	else {
		onground = false;
	}
	hitbox.setPosition({ x, y });
	window.draw(hitbox);
}



