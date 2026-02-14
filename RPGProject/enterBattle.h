#pragma once
#include<iostream>
#include "BattleMachine.h"
#include "Character.h"
#include "Enemy.h"
#include "Player.h"


inline void enterBattle(Character* player) {
  //clears the screen
  std::cout << "\033[2J\033[1;1H";

  //creates a new battle, which loads the player and a random enemy
  BattleMachine battle(player);

  std::cin.ignore();

  //player and enemy take turns as long as neither of them dies or runs away
  while (battle.status == Status::ATWAR) {
    //take a turn
    battle.takeTurn();
    //have the player press enter to continue
    }

  //displays the results of the battle
  battle.battleResults();
  std::cin.ignore();
  std::cin.get();
  std::cout << "\033[2J\033[1;1H";
  }
