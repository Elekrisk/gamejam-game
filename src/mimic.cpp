#include "mimic.hpp"
#include "asset_manager.hpp"

sf::Texture const EMPTY{};

Mimic::Mimic(sf::Vector2i position)
: Entity(position, &EMPTY)
{
    sf::Texture *texture{asset_manager.load<sf::Texture>("assets/chest.png")};
    sprite.setTexture(*texture, true);
}