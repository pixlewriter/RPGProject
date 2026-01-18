#pragma once
#include "Character.h"
class Enemy :
    public Character
{
    using Character::Character;
private:
    double fear;
    double recklessness;
public:
    void damageDealt(double damage) override;
};

