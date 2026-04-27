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

//Alan
inline Enemy* alanTheAhole() {
    Enemy* enemy = new Enemy(250, 100, 25);
    enemy->setFear(1);
    enemy->setRecklessness(5);

    std::cout << "Alan the A-hole has confronted you. The time for de-escalating is over. Careful though, he's strong and not in the mood to run." << std::endl;
    return enemy;
}

//pacific tree octopus
inline Enemy* pacificTreeOctopus() {
  Enemy* enemy = new Enemy(300, 40, 40);
  enemy->setFear(7);
  enemy->setRecklessness(1);

  std::cout << "A rare Pacific Tree Octopus stands before. Are you sure you want to threaten it?" << std::endl;
  return enemy;
}

//land shark
inline Enemy* landShark() {
  Enemy* enemy = new Enemy(150, 100, 10);
  enemy->setFear(0);
  enemy->setRecklessness(9);

  std::cout << "It's a land shark. His mobility is limited, but his teeth are sharp.";
  return enemy;
}

//RA
inline Enemy* rA() {
  Enemy* enemy = new Enemy(1000, 1000, 1000);
  enemy->setFear(0);
  enemy->setRecklessness(0);

  std::cout << "You look up to see an RA coming towards you. You're definitely in trouble. Better run!";
  return enemy;
}

//doofenshmirtz
inline Enemy* doofenshmirtz() {
  Enemy* enemy = new Enemy(350, 30, 100);
  enemy->setFear(1);
  enemy->setRecklessness(10);

  std::cout << "It's Dr. Doofenshmirtz. The aliens must have captured him and are cloning him to be their henchmen.";
  std::cout << "He'll probably destroy himself if you don't" << std::endl;
  return enemy;
}
