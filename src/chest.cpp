#include "chest.hpp"
#include "asset_manager.hpp"
#include "world.hpp"
#include "item_entity.hpp"
#include "key.hpp"

Chest::Chest(World* world, sf::Vector2i position, std::unique_ptr<Item> contents)
    : Entity{world, position, asset_manager.load<sf::Texture>("assets/chest.png")},
      contents{std::move(contents)},
      open_{false}
{
    obstructs = true;
}

void Chest::open()
{
    if (!open_)
    {
        world->add_entity(new Item_Entity{this->world, position, std::move(contents)});
        sprite.setTexture(*asset_manager.load<sf::Texture>("assets/chest_open.png"), true);
        open_ = true;
    }
}

void Chest::interact(std::unique_ptr<Item>& item)
{
    Key* key = dynamic_cast<Key*>(&*item);
    if (key != nullptr)
    {
        open();
        item = nullptr;
    }
}
