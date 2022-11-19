#include "item_entity.hpp"

Item_Entity::Item_Entity(sf::Vector2i position, std::unique_ptr<Item> item)
: Entity(position, item->get_sprite().getTexture()), item{std::move(item)}
{}

std::unique_ptr<Item> Item_Entity::steal_item()
{
    return std::move(item);
}