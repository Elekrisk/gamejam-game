#include "player.hpp"
#include "world.hpp"
#include "asset_manager.hpp"
#include "item_entity.hpp"
#include "geiger.hpp"
#include "item.hpp"

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

void Player::pick_up(World &world)
{
    std::vector<Item_Entity *> items{};
    for (Entity *ent : world.get_entities())
    {
        if (ent->get_position() != position)
        {
            continue;
        }
        Item_Entity *item = dynamic_cast<Item_Entity *>(ent);
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

void Player::put_down(World &world)
{
    if (item != nullptr)
    {
        world.add_entity(new Item_Entity{position, std::move(item)});
    }
}

void Player::interact(World &world)
{
    std::vector<Entity *> entities{};
    for (Entity *ent : world.get_entities())
    {
        if (ent->get_position() != position || dynamic_cast<Player*>(ent) != nullptr)
        {
            continue;
        }
        entities.push_back(ent);
    }

    for (Entity *ent : entities)
    {
        ent->interact(item, world);
    }
}

void Player::draw(RenderView &view)
{
    Entity::draw(view);
    if (item != nullptr)
    {
        item->get_sprite().setPosition(sf::Vector2f{position});
        item->get_sprite().setScale(sf::Vector2f{0.35, 0.35});
        view.draw(item->get_sprite());
    }
}

void Player::move_to(sf::Vector2i target)
{
    Entity::move_to(target);
    Geiger* geiger = dynamic_cast<Geiger*>(&*item);
    if (geiger != nullptr)
    {
        geiger->update();
    }
}
void Player::destroy_item()
{
    item = nullptr;
}
