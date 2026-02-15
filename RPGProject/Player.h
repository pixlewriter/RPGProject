#pragma once
#include "Character.h"
#include "InventoryItem.h"
#include<list>

class Player :
    public Character
{
    using Character::Character;
public:
  std::list<InventoryItem> inventory;
    void attack(Character& character) override;
    void heal() override;
    void damageDealt(double damage) override;
};


