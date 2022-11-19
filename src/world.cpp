#include "world.hpp"
#include "player.hpp"
#include "item_entity.hpp"
#include "geiger.hpp"
#include "mimic.hpp"
#include "key.hpp"
#include "level_parser.hpp"

#include <fstream>
#include <sstream>

World::World() : entities{}, walls{}, player{} {}

World::~World()
{
    for (Entity *ent : entities)
    {
        delete ent;
    }
}

void World::add_entity(Entity *entity)
{
    Player* player_entity = dynamic_cast<Player*>(entity);
    if (player_entity != nullptr)
    {
        player = player_entity;
    }
    entities.push_back(entity);
}

void World::kill_entity(Entity *entity)
{
    for (auto it{entities.begin()}; it < entities.end(); ++it)
    {
        if (*it == entity)
        {
            delete *it;
            entities.erase(it);
        }
    }
}

std::vector<Entity *> const &World::get_entities() const
{
    return entities;
}

std::vector<Wall> const &World::get_walls() const
{
    return walls;
}

Player* World::get_player() const
{
    return player;
}

bool World::can_move(sf::Vector2i pos, Wall::Direction dir) const
{
    sf::Vector2i target{pos};
    switch (dir)
    {
    case Wall::Direction::North:
        target.y -= 1;
        break;
    case Wall::Direction::South:
        target.y += 1;
        break;
    case Wall::Direction::East:
        target.x += 1;
        break;
    case Wall::Direction::West:
        target.x -= 1;
        break;
    }
    for (Wall const &wall : walls)
    {
        Wall::Direction blocking_dir;
        if (wall.position == pos)
        {
            blocking_dir = dir;
        }
        else if (wall.position == target)
        {
            blocking_dir = opposite(dir);
        }
        else
        {
            continue;
        }

        if (wall.direction == blocking_dir)
        {
            return false;
        }
    }
    return true;
}

World World::load_level(std::string const &path)
{
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();

    World world{};

    Lexer lexer{buffer.str()};
    std::vector<Token> tokens = lexer.lex_all();
    Parser parser{tokens};
    File file_obj;
    if (!parser.parse_file(file_obj))
    {
        throw "Cannot parse level file";
    }
    int width{-1};
    int height{-1};
    for (File::Part &part : file_obj.parts)
    {
        if (part.title == "Meta")
        {
            width = part.properties["Width"];
            height = part.properties["Height"];
        }
        if (part.title == "Walls")
        {
            for (File::Object &obj : part.objects)
            {
                if (obj.name == "Wall")
                {
                    world.walls.push_back(Wall{{obj.params[0], obj.params[1]}, static_cast<Wall::Direction>(obj.params[2])});
                }
                else
                {
                    throw "Invalid object in Walls part";
                }
            }
        }
        if (part.title == "Entities")
        {
            for (File::Object &obj : part.objects)
            {
                int x = obj.params[0];
                int y = obj.params[1];
                std::string &name = obj.name;
                if (name == "Player")
                {
                    world.add_entity(new Player{{x, y}});
                }
                else if (name == "Geiger")
                {
                    world.add_entity(new Item_Entity{{x, y}, std::make_unique<Geiger>()});
                }
                else if (name == "Mimic")
                {
                    world.add_entity(new Mimic{{x,y}});
                }
                else if (name == "Key")
                {
                    world.add_entity(new Item_Entity{{x,y}, std::make_unique<Key>()});
                }
                else
                {
                    throw "what";
                }
            }
        }
    }

    for (int i = 0; i < 4; i ++)
    {
        world.walls.push_back(Wall{{10, 10}, static_cast<Wall::Direction>(i)});
    }
    return world;
}