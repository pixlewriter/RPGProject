#pragma once
#include<iostream>
#include "BattleMachine.h"
#include "Character.h"
#include "Enemy.h"
#include "Player.h"


inline void enterBattle() {

  //creates a new battle, which loads the player and a random enemy
  BattleMachine battle;

  std::cin.ignore();

  //player and enemy take turns as long as neither of them dies or runs away
  while (battle.status == Status::ATWAR) {
    battle.takeTurn();
    }

  //displays the results of the battle
  battle.battleResults();
  }
