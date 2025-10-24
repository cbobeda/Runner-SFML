#include "TileManager.h"


TileManager::TileManager(sf::RenderWindow& window) : win(&window), tileText(std::make_shared<sf::Texture>()), coinText(std::make_shared<sf::Texture>())
{
	srand(time(0));

	if (!tileText->loadFromFile("assets/map/tile.png"))
	{
		std::cout << "failed to load tile texture \n";
	}

	if (!coinText->loadFromFile("assets/map/coin.png"))
	{
		std::cout << "failed to load coin texture \n";
	}

	tileVector.reserve(generation.getTime().size());
	int random;
	for (auto& time : generation.getTime())
	{
		random = rand() % 4;
		if (random == 0)
			coinVector.emplace_back(coinText, (time * tileWidth * 5) + 120.f , generation.getDomfreq().at((int)time) * 0.1 + win->getSize().y * 0.5 - 60.f);
		tileVector.emplace_back(tileText, time * tileWidth * 5, generation.getDomfreq().at((int)time) * 0.1 + win->getSize().y * 0.5);
		tileVector.back().getSprite()->setColor(sf::Color(std::sinf(time) * 127 + 127, std::cosf(time) * 127 + 127, std::sinf(time + 3.14159265359) * 127 + 127));
	}
}

void TileManager::drawTiles()
{
	for (auto& tile : tileVector)
	{
		tile.draw(*win);
	}
	for (auto& coin : coinVector)
	{
		coin.draw(*win);
	}
}

void TileManager::update(float deltaTime)
{
	for (auto& tile : tileVector)
	{
		tile.update(deltaTime, 500.f);
	}
	for (auto& coin : coinVector)
	{
		coin.update(deltaTime, 500.f);
	}


	// seconde passe : recycler les tuiles qui sont compl�tement sorties � gauche

	const float leftThreshold = -static_cast<float>(tileWidth) * 5; // ou sprite width si variable
	for (auto& tile : tileVector)
	{
		if (tile.getSprite()->getPosition().x <= leftThreshold)
		{
			// trouver la tuile la plus � droite
			float maxX = std::numeric_limits<float>::lowest();
			for (auto& t : tileVector) {
				maxX = std::max(maxX, t.getSprite()->getPosition().x);
			}
			// placer la tuile recycl�e directement � droite de la tuile la plus � droite
			tile.getSprite()->setPosition(sf::Vector2f(maxX + static_cast<float>(tileWidth) * 5,tile.getSprite()->getPosition().y));
			tile.getSprite()->setColor(sf::Color(std::sinf(colorClock.getElapsedTime().asSeconds()) * 127 + 127, std::cosf(colorClock.getElapsedTime().asSeconds()) * 127 + 127, std::sinf(colorClock.getElapsedTime().asSeconds() + 3.14159265359) * 127 + 127));
			int random;
			random = rand() % 4;
			if (random == 0)
				coinVector.emplace_back(coinText, (maxX + static_cast<float>(tileWidth) * 5) + 120.f, (tile.getSprite()->getPosition().y) - 60.f);
		}
	}
	std::erase_if(coinVector, [](Coins& c) {
		std::shared_ptr<sf::Sprite> spr = c.getSprite();
		return spr && spr->getPosition().x <= -10.f;
		});
}