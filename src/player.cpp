#include "player.hpp"
#include "world.hpp"
#include "asset_manager.hpp"
#include "item_entity.hpp"

// Player::Player(sf::Vector2i position, sf::Texture &&texture)
//     : Entity{position, texture}
// {
// }

sf::Texture const EMPTY{};

Player::Player(sf::Vector2i position) : Entity{position, &EMPTY}
{
    sf::Texture *texture{asset_manager.load<sf::Texture>("assets/player.png")};
    sprite.setTexture(*texture, true);
}

void Player::pick_up(World& world)
{
    std::vector<Item_Entity*> items{};
    for (Entity *ent : world.get_entities())
    {
        Item_Entity* item = dynamic_cast<Item_Entity*>(ent);
        if (item != nullptr)
        {
            items.push_back(item);
        }
    }

    if (items.size() == 0)
    {
        return;
    }

    if (item != nullptr)
    {
        put_down(world);
    }

    item = items[0]->steal_item();
    world.kill_entity(items[0]);
}