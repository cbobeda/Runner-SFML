#include <SFML/Graphics.hpp>
#include <thread>
#include "LevelGenerator.h"
#include "TileManager.h"
#include "Player.h"
#include "SaveManager.h"
#include "SoundManager.h"

int main()
{
    bool isHome = true;
    bool isPause = false;

    sf::Font neon("assets/font/Neon.ttf");
    sf::Text title(neon, "Runner", 70);
    sf::Text instruction(neon, "Press SPACE to start", 30);
    sf::Text pauseText(neon, "PAUSED", 30);
    sf::Text scoreText(neon, "score", 30);

    SaveManager sav;
    int score = sav.getSavedCoins();

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()), "SFML works!", sf::State::Fullscreen);
    window.setVerticalSyncEnabled(true);
    title.setPosition(sf::Vector2f(window.getSize().x / 2 - title.getLocalBounds().size.x / 2, window.getSize().y / 2 - title.getLocalBounds().size.y / 2 - 100));
    instruction.setPosition(sf::Vector2f(window.getSize().x / 2 - instruction.getLocalBounds().size.x / 2, window.getSize().y / 2 - instruction.getLocalBounds().size.y / 2 + 100));
    pauseText.setPosition(sf::Vector2f(window.getSize().x / 2 - pauseText.getLocalBounds().size.x / 2, window.getSize().y / 2 - pauseText.getLocalBounds().size.y / 2));


    TileManager manager(window);


    sf::Clock deltaTime;
    sf::Clock buttonCd;

    SoundManager sManager(&window);


    Player player;
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
                    sManager.pause();
                    deltaTime.restart();
                }
                else
                {
                    isPause = false;
                    sManager.play();
                    deltaTime.restart();
                }
                buttonCd.restart();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isHome)
            {
                isHome = false;
                sManager.play();
                deltaTime.restart();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                sManager.soundDown();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                sManager.soundUp();
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
            sManager.drawSoundbar(&window);
            window.draw(scoreText);
            window.setActive(false);
            std::thread t1(&TileManager::update,&manager,deltaTime.getElapsedTime().asSeconds());
            t1.join();
            window.setActive(true);
            player.update(window, deltaTime.getElapsedTime().asSeconds(), manager.gettileVector(), manager.getconsttileVector(), manager.getcoinVector(), manager.getconstcoinVector());
       
            window.display();


            deltaTime.restart();

        }

    }

    sav.savecoins(score);
}