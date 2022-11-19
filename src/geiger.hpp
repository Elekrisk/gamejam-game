#include "item.hpp"
#include <SFML/Audio.hpp>

class Geiger : public Item
{
    sf::Sound count;
    float get_closest();
public:
    Geiger();

    virtual void use_item(Entity* target) override;
    void update();
};