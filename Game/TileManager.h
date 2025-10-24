#pragma once

#include <vector>
#include <random>
#include "Tile.h"
#include "Coins.h"
#include "LevelGenerator.h"
class TileManager
{
	public:

		TileManager(sf::RenderWindow& window);
		void update(float deltaTime);
		void drawTiles();

	private:
		LevelGenerator generation;
		sf::RenderWindow* win;
		const float tileWidth = 60.f;
		std::vector<Tile> tileVector;
		std::vector<Coins> coinVector;
		sf::Clock colorClock;

};

