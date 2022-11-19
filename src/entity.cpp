#include "entity.hpp"

Entity::Entity(sf::Vector2i position, sf::Texture const* texture)
    : Sprite{texture}, position{position}
{
}

sf::Vector2i Entity::get_position() const
{
    return position;
}

void Entity::move_to(int x, int y)
{
    position.x = x;
    position.y = y;
}