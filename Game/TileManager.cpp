#include "TileManager.h"


TileManager::TileManager(sf::RenderWindow& window) : win(&window)
{

	int count = static_cast<int>(win->getSize().x) / static_cast<int>(tileWidth); // truncates

	tileVector.reserve(count + 1);
	for (int i = 0; i <= count; ++i) {
		tileVector.emplace_back("assets/map/tile.png", i * tileWidth, win->getSize().y - tileWidth);
	}
}

void TileManager::drawTiles()
{
	for (auto& tile : tileVector)
	{
		tile.draw(*win);
	}
}

void TileManager::update(float deltaTime)
{
	for (auto& tile : tileVector)
	{
		tile.update(deltaTime, 1000.f);
	}


	// seconde passe : recycler les tuiles qui sont complètement sorties à gauche

	const float leftThreshold = -static_cast<float>(tileWidth); // ou sprite width si variable
	for (auto& tile : tileVector)
	{
		if (tile.getSprite()->getPosition().x <= leftThreshold)
		{
			// trouver la tuile la plus à droite
			float maxX = std::numeric_limits<float>::lowest();
			for (auto& t : tileVector) {
				maxX = std::max(maxX, t.getSprite()->getPosition().x);
			}
			// placer la tuile recyclée directement à droite de la tuile la plus à droite
			tile.getSprite()->setPosition(sf::Vector2f(maxX + static_cast<float>(tileWidth), win->getSize().y - tileWidth));
		}
	}
}