#include <SFML/Graphics.hpp>
#include "LevelGenerator.h"
#include "TileManager.h"
#include "Player.h"

int main()
{
    bool isHome = true;
    bool isPause = false;
    sf::Font neon("assets/font/Neon.ttf");
    sf::Text title(neon, "Runner", 70);
    sf::Text instruction(neon, "Press SPACE to start", 30);
    sf::Text pauseText(neon, "PAUSED", 30);

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()), "SFML works!", sf::State::Fullscreen);

    title.setPosition(sf::Vector2f(window.getSize().x / 2 - title.getLocalBounds().size.x / 2, window.getSize().y / 2 - title.getLocalBounds().size.y / 2 - 100));
    instruction.setPosition(sf::Vector2f(window.getSize().x / 2 - instruction.getLocalBounds().size.x / 2, window.getSize().y / 2 - instruction.getLocalBounds().size.y / 2 + 100));
    pauseText.setPosition(sf::Vector2f(window.getSize().x / 2 - pauseText.getLocalBounds().size.x / 2, window.getSize().y / 2 - pauseText.getLocalBounds().size.y / 2));

    window.setFramerateLimit(60);
    TileManager manager(window);


    sf::Clock deltaTime;
    sf::Clock buttonCd;


    sf::Music m;
    m.openFromFile("assets/music/test.ogg");
    m.setLooping(true);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && buttonCd.getElapsedTime().asSeconds() > 0.5f)
            {
                if (!isPause)
                {
                    isPause = true;
                    m.pause();
                    deltaTime.restart();
                }
                else
                {
                    isPause = false;
                    m.play();
                    deltaTime.restart();
                }
                buttonCd.restart();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isHome)
            {
                isHome = false;
                m.play();
                deltaTime.restart();
            }
            
        }
        if (isHome)
        {
            window.clear();
            window.draw(title);
            window.draw(instruction);
            instruction.setFillColor(sf::Color(255, 255, 255, std::sinf(deltaTime.getElapsedTime().asSeconds()) * 100 + 150));
            window.display();
        }
        else if (isPause)
        {
            window.clear();
            window.draw(pauseText);
            pauseText.setFillColor(sf::Color(255, 255, 255, std::sinf(deltaTime.getElapsedTime().asSeconds()) * 100 + 150));
            window.display();
        }
        if(!isHome && !isPause )
        {
            window.clear();
            manager.drawTiles();
            manager.update(deltaTime.getElapsedTime().asSeconds());
            window.display();
            deltaTime.restart();
        }

        
    }
}