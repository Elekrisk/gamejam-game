#include "entity.hpp"

Entity::Entity(World* world, sf::Vector2i position, sf::Texture const *texture)
    : Sprite{texture}, world{world}, position{position}
{
    obstructs = false;
}

sf::Vector2i Entity::get_position() const
{
    return position;
}

void Entity::update_world_pointer(World* world)
{
    this->world = world;
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

void Entity::interact(std::unique_ptr<Item> &)
{
}

void Entity::toggle_circuit(int id)
{
}

bool Entity::does_obstruct() const
{
    return obstructs;
}


void Entity::set_obstructs(bool obstructs)
{
    this->obstructs = obstructs;
}
