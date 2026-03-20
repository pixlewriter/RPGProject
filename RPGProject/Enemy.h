#pragma once
#include "Character.h"
#include<iostream>

class Enemy :
    public Character
{
    using Character::Character;
private:
    int fear = 0;
    int recklessness = 0;
public:
    void damageDealt(double damage) override;
    int getFear();
    int getRecklessness();
    void setFear(int num);
    void setRecklessness(int num);
};

//functions for geneating various enemies

//alien worker
inline Enemy* alienWorker() {
  Enemy* enemy = new Enemy(200, 30, 10);
  enemy->setFear(5);
  enemy->setRecklessness(2);

  std::cout << "An alien worker confronts you." << std::endl;
  return enemy;
}

//alien soldier
inline Enemy* alienSoldier() {
  Enemy* enemy = new Enemy(700, 40, 5);
  enemy->setFear(3);
  enemy->setRecklessness(7);

  std::cout << "An alien soldier confronts you." << std::endl;
  return enemy;
}

//intergalactic technician
inline Enemy* intergalacticTechnician() {
  Enemy* enemy = new Enemy(250, 100, 25);
  enemy->setFear(8);
  enemy->setRecklessness(2);

  std::cout << "An intergalactic technician stands in front of you. He's very strong but fragile and fearful." << std::endl;
  return enemy;
}
