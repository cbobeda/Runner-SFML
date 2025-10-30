#include <SFML/Graphics.hpp>
#include <thread>
#include <future>
#include "LevelGenerator.h"
#include "TileManager.h"
#include "Player.h"
#include "SaveManager.h"
#include "SoundManager.h"

int main()
{
    bool isHome = true;
    bool isPause = false;

    SaveManager sav;
    int score = sav.getSavedScore();
    int coins = 1;

    sf::Font neon("assets/font/Neon.ttf");
    sf::Text title(neon, "Runner", 70);
    sf::Text instruction(neon, "Press SPACE to start", 30);
    sf::Text pauseText(neon, "PAUSED", 30);
    sf::Text scoreText(neon, "Last score : " + std::to_string(score), 30);
    sf::Text coinText(neon, "coins : " + std::to_string(coins), 30);
    sf::Text death(neon, "You are dead", 70);

    

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()), "SFML works!", sf::State::Fullscreen);
    window.setVerticalSyncEnabled(true);
    title.setPosition(sf::Vector2f(window.getSize().x / 2 - title.getLocalBounds().size.x / 2, window.getSize().y / 2 - title.getLocalBounds().size.y / 2 - 100));
    instruction.setPosition(sf::Vector2f(window.getSize().x / 2 - instruction.getLocalBounds().size.x / 2, window.getSize().y / 2 - instruction.getLocalBounds().size.y / 2 + 100));
    pauseText.setPosition(sf::Vector2f(window.getSize().x / 2 - pauseText.getLocalBounds().size.x / 2, window.getSize().y / 2 - pauseText.getLocalBounds().size.y / 2));
    death.setPosition(sf::Vector2f(window.getSize().x / 2 - death.getLocalBounds().size.x / 2, window.getSize().y / 2 - death.getLocalBounds().size.y / 2 - 100));
    coinText.setPosition(sf::Vector2f(window.getSize().x / 2, 0));

    TileManager manager(window);


    sf::Clock deltaTime;
    sf::Clock buttonCd;

    SoundManager sManager(&window);


    Player player;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
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
                score = 0;
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
            window.draw(scoreText);
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
        if (!player.alive)
        {
            window.clear();
            instruction.setString("Press escape to leave");
            window.draw(instruction);
            window.draw(death);
            death.setFillColor(sf::Color(255, 255, 255, std::sinf(deltaTime.getElapsedTime().asSeconds()) * 100 + 150));
            window.display();
        }
        if(!isHome && !isPause && player.alive)
        {
            window.clear();
            manager.drawTiles();
            sManager.drawSoundbar(&window);
            scoreText.setString("score : " + std::to_string(score));
            coinText.setString("coins : " + std::to_string(coins));
            window.draw(scoreText);
            window.draw(coinText);
            window.setActive(false);
            auto future = std::async(&TileManager::update,&manager,deltaTime.getElapsedTime().asSeconds());
            score = score + (coins * future.get() * deltaTime.getElapsedTime().asSeconds());
            window.setActive(true);
            player.update(window, deltaTime.getElapsedTime().asSeconds(), manager.gettileVector(), manager.getconsttileVector(), manager.getcoinVector(), manager.getconstcoinVector());
            if (player.coin) {
                coins += 1;
                player.coin = false;
            }
       
            window.display();


            deltaTime.restart();

        }

    }

    sav.saveScore(score);
}