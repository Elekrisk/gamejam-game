#include "wall.hpp"


Wall::Direction opposite(Wall::Direction dir)
{
    switch (dir)
    {
        case Wall::Direction::North: return Wall::Direction::South;
        case Wall::Direction::South: return Wall::Direction::North;
        case Wall::Direction::West: return Wall::Direction::East;
        case Wall::Direction::East: return Wall::Direction::West;
    }
}