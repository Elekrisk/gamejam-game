#include "player.hpp"
#include "asset_manager.hpp"

// Player::Player(sf::Vector2i position, sf::Texture &&texture)
//     : Entity{position, texture}
// {
// }

Player::Player(sf::Vector2i position) : Entity{position, sf::Texture{}}
{
    sf::Texture *texture{asset_manager.load<sf::Texture>("assets/player.png")};
    sprite.setTexture(*texture, true);
}