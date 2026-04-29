#pragma once
#include<iostream>
#include "BattleMachine.h"
#include "Character.h"
#include "Enemy.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include "audio_manager.h"

inline void enterBattle(Character* player, WASDNode* location) {
  start_music("battle_music1 (1).wav", true);
  //clears the screen
  std::cout << "\033[2J\033[1;1H";

  //creates a new battle, which loads the player and a random enemy
  BattleMachine battle(player, location);

  //diplay a menu
  std::vector<std::string> options{ "Press enter to continue" };
  ListMenu noChoice(" ", options);
  int choice = noChoice.printDynamicMenu();
  std::cout << "\033[2J\033[1;1H";


  //player and enemy take turns as long as neither of them dies or runs away
  while (battle.status == Status::ATWAR) {
    //take a turn
    battle.takeTurn();
    //have the player press enter to continue
    }

  //displays the results of the battle
  battle.battleResults();
  //diplay a menu
  noChoice.printDynamicMenu();
  std::cout << "\033[2J\033[1;1H";
  stop_music();
  }
