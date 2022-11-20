#include "geiger.hpp"
#include "asset_manager.hpp"

#include <cmath>


Geiger::Geiger()
: Item{asset_manager.load<sf::Texture>("assets/geiger.png")}, count{}
{
    count.setBuffer(*asset_manager.load<sf::SoundBuffer>("assets/geiger.wav"));
    count.setLoop(true);
    count.play();
    this->update(INFINITY);
}


void Geiger::update(float dist)
{
    float dist_to_silent = 5.0f;

    count.setVolume(std::clamp(100.0f * (1.0f - dist / dist_to_silent), 0.0f, 100.0f));
    count.setPitch(std::clamp(10-dist*2, 0.0f, 10.0f));
}