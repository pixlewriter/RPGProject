#pragma once
#include "Character.h"
#include "Enemy.h"
#include "Player.h"

//enum types to determine whose turn it is and whether anyone is dead or running away
enum Status {ATWAR,PLAYERDEAD,PLAYERRUN,ENEMYDEAD,ENEMYRUN}; 
enum Turn { PLAYER, ENEMY };
  

class BattleMachine {
private:
  Character* enemy;
  Character* player;

  //prints the results of the turn
  void turnResults();

  //check to see if either charcter is dead, and update the status accordingly
  void isDead();

public:
  Status status = Status::ATWAR;
  Turn turn = Turn::PLAYER;

  //creates a battle machine, selects an enemy, and sets the player stats
  BattleMachine(Character* player);

  //takes a turn depending on whose turn it is, and prints the results of the turn
  void takeTurn();
    //at the end of the battle, prints the results of the battle
  void battleResults();
 
};
