#include "item_entity.hpp"

Item_Entity::Item_Entity(World* world, sf::Vector2i position, std::unique_ptr<Item> item)
: Entity(world, position, nullptr), item{std::move(item)}
{
    sprite = this->item->get_sprite();
}

std::unique_ptr<Item> Item_Entity::steal_item()
{
    return std::move(item);
}