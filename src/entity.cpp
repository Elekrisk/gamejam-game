#include "entity.hpp"

Entity::Entity(sf::Vector2i position, sf::Texture const *texture)
    : Sprite{texture}, position{position}
{
}

sf::Vector2i Entity::get_position() const
{
    return position;
}

void Entity::move_to(sf::Vector2i target)
{
    position.x = target.x;
    position.y = target.y;
}

void Entity::draw(RenderView &view)
{
    sprite.setPosition(sf::Vector2f{position});
    sprite.setScale(sf::Vector2f{1.0, 1.0});
    view.draw(sprite);
}

void Entity::interact(std::unique_ptr<Item> &item, World &world)
{
}

void Entity::toggle_circuit(int id)
{
}
