#pragma once

#include "item.hpp"

class Key : public Item
{
public:
    Key();

    virtual void use_item(Entity* target) override;
};
