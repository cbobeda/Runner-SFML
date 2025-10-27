#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class SoundManager
{
	public:
		SoundManager(sf::RenderWindow* window);
		void soundUp();
		void soundDown();
		void pause();
		void play();
		void drawSoundbar(sf::RenderWindow* window);

	private:
		sf::Music m;
		sf::RectangleShape bar;
};

