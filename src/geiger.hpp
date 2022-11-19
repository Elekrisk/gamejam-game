#include "item.hpp"

class Geiger : public Item
{
public:
    Geiger();

    virtual void use_item(Entity* target, World& world) override;
};