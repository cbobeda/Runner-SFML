#include "SoundManager.h"

SoundManager::SoundManager(sf::RenderWindow* window)
{
    if (!m.openFromFile("assets/music/test.ogg"))
    {
        std::cout << "Erreur lors du chargement de la music \n";
    }
    m.setLooping(true);

    bar.setPosition(sf::Vector2f(window->getSize().x - 110.f, 10.f));
    bar.setSize(sf::Vector2f(m.getVolume(), 0));
}

void SoundManager::soundUp()
{
    if(m.getVolume() < 100)
        m.setVolume(m.getVolume() + 1);
}

void SoundManager::soundDown()
{
    if (m.getVolume() > 0)
        m.setVolume(m.getVolume() - 1);
}

void SoundManager::play()
{
    m.play();
}

void SoundManager::pause()
{
    m.pause();
}

void SoundManager::drawSoundbar(sf::RenderWindow* window)
{
    bar.setSize(sf::Vector2f(m.getVolume(), 10.f));
    window->draw(bar);
}