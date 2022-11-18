#include "player.hpp"

// Player::Player(sf::Vector2i position, sf::Texture &&texture)
//     : Entity{position, texture}
// {
// }

Player::Player(sf::Vector2i position) : Entity{position, sf::Texture{}}
{
    sf::Texture* texture {new sf::Texture{}};
    texture->loadFromFile("assets/player.png");
    sprite.setTexture(*texture, true);
}