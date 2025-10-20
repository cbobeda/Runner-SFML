#include <SFML/Graphics.hpp>
#include "TileManager.h"
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()), "SFML works!", sf::State::Fullscreen);
    window.setFramerateLimit(60);
    TileManager manager(window);
    sf::Clock deltaTime;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        manager.drawTiles();
        manager.update(deltaTime.getElapsedTime().asSeconds());
        window.display();

        deltaTime.restart();
    }
}