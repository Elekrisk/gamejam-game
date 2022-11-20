#include "item.hpp"
#include <SFML/Audio.hpp>

class Geiger : public Item
{
    sf::Sound count;
public:
    Geiger();
    void update(float dist);
};