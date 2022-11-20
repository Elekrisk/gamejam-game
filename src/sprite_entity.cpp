#include "sprite_entity.hpp"
#include "asset_manager.hpp"
#include "concat.hpp"

SpriteEntity::SpriteEntity(World *world, sf::Vector2i position, std::string const &name)
    : Entity{world, position, asset_manager.load<sf::Texture>(concat("assets/", name, ".png"))}
{
}
