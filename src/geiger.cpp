#include "geiger.hpp"
#include "asset_manager.hpp"


Geiger::Geiger()
: Item{asset_manager.load<sf::Texture>("assets/geiger.png")}, count{}
{
    count.setBuffer(*asset_manager.load<sf::SoundBuffer>("assets/geiger.wav"));
    count.setLoop(true);
    count.play();
}

void Geiger::use_item(Entity* target) {}
void Geiger::update()
{
    count.setPitch(get_closest());
}

float Geiger::get_closest()
{
    return 2.0f;
}