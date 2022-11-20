#include "chest.hpp"
#include "asset_manager.hpp"
#include "world.hpp"
#include "item_entity.hpp"
#include "key.hpp"

Chest::Chest(sf::Vector2i position, std::unique_ptr<Item> contents)
    : Entity{position, asset_manager.load<sf::Texture>("assets/chest.png")},
      contents{std::move(contents)},
      open_{false}
{
}

void Chest::open(World &world)
{
    if (!open_)
    {
        world.add_entity(new Item_Entity{position, std::move(contents)});
        sprite.setTexture(*asset_manager.load<sf::Texture>("assets/chest_open.png"), true);
        open_ = true;
    }
}

void Chest::interact(std::unique_ptr<Item>& item, World& world)
{
    Key* key = dynamic_cast<Key*>(&*item);
    if (key != nullptr)
    {
        open(world);
        item = nullptr;
    }
}
