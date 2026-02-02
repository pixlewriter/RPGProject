#pragma once
#include "Character.h"
class Player :
    public Character
{
    using Character::Character;
public:
    void attack(Character& character) override;
    void heal() override;
    void damageDealt(double damage) override;
};


