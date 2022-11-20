#include "geiger.hpp"
#include "asset_manager.hpp"


Geiger::Geiger()
: Item{asset_manager.load<sf::Texture>("assets/geiger.png")}, count{}
{
    count.setBuffer(*asset_manager.load<sf::SoundBuffer>("assets/geiger.wav"));
    count.setLoop(true);
    count.play();
}


void Geiger::update(float dist)
{
    count.setPitch(10-dist);
}