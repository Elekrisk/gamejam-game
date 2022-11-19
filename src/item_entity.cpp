#include "item_entity.hpp"

Item_Entity::Item_Entity(sf::Vector2i position, Item* item)
: Entity(position, item->get_sprite().getTexture()), item{item}
{}