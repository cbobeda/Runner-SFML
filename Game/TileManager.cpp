#include "TileManager.h"


TileManager::TileManager(sf::RenderWindow& window) : win(&window)
{

	tileVector.reserve(generation.getTime().size());
	for (auto& time : generation.getTime())
	{
		tileVector.emplace_back("assets/map/tile.png", time * tileWidth * 5, generation.getDomfreq().at((int)time) * 0.1 + win->getSize().y * 0.5);
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

	const float leftThreshold = -static_cast<float>(tileWidth) * 5; // ou sprite width si variable
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
			tile.getSprite()->setPosition(sf::Vector2f(maxX + static_cast<float>(tileWidth) * 5,tile.getSprite()->getPosition().y));
		}
	}
}

const std::vector<Tile>& TileManager::getVector() const { return tileVector; }