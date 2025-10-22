#include <SFML/Graphics.hpp>

#include "Player.h"
#include "soltemp.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({500, 500}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    std::vector<soltemp> sol = { {0, 70}, {20, 70} , {40, 70} };
    Player player;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        window.clear();
        player.update(window, sol);
        window.display();
    }
}