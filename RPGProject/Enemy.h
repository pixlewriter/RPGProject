#pragma once
#include "Character.h"
class Enemy :
    public Character
{
    using Character::Character;
private:
    int fear = 0;
    double recklessness = 1;
public:
    void damageDealt(double damage) override;
    int getFear();
    double getRecklessness();
    void setFear(int num);
    void setRecklessness(double num);
};

