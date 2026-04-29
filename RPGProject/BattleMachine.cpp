#include<iostream>
#include<random>
#include<string>
#include<ctime>
#include "BattleMachine.h"
#include "Character.h"
#include "Enemy.h"
#include "Player.h"
#include "audio_manager.h"
#include "Menu.h"


//creates a new battle, spawning the player and a random enemy

BattleMachine::BattleMachine(Character* player) {
  //Spawns the player and sets stats
  Enemy* newEnemy = nullptr;

  //pick a random number between 1 and 3 to determine which enemy to generate
  std::default_random_engine engine{ static_cast<unsigned>(time(0)) };
  std::uniform_int_distribution<unsigned> randomInt{ 1,3 };
  unsigned decisionMaker = randomInt(engine);

  //a switch statement to decide which enemy to generate
  
  if (player->alanEncounter == 1) {
      newEnemy = alanTheAhole();
  }
  else
  {
      switch (decisionMaker) {

      case 1:
          //generated a alien worker
          newEnemy = alienWorker();
          break;

      case 2:
          //generate a alien soldier
          newEnemy = alienSoldier();
          break;

      case 3:
          //generate an intergalactic technician
          newEnemy = intergalacticTechnician();
          break;
      }
  }
  this->enemy = newEnemy;
  this->player = player;
}
int BattleMachine::takeTurn() {
  //allows the player to go if it is players turn
  if (turn == Turn::PLAYER) {
    //diplay a menu
    std::vector<std::string> options{ "Attack", "Heal", "Run Away" };
    ListMenu turnOptions("Turn Options", options);
    int choice = turnOptions.printDynamicMenu();

    std::cout << "\033[2J\033[1;1H";

    switch (choice) {
    case 1:
      //player attacks the enemy
      player->attack(*enemy);

      play_effect("hit_effect.wav");
      
      std::cout << "You attacked the enemy" << std::endl;
      break;

    case 2:
      //player heals
      player->heal();
      std::cout << "You healed" << std::endl;
      break;

    case 3:
      //player runs away
      status = Status::PLAYERRUN;
      break;
    }

    //change the turn
    turn = Turn::ENEMY;
  }
  
  //otherwise the enemy goes
  else {
    std::cout << "\033[2J\033[1;1H";
   //pick a random number between 1 and 100 to determine enemy move
    std::default_random_engine engine{ static_cast<unsigned>(time(0)) };
    std::uniform_int_distribution<unsigned> randomInt{ 1,100 };
    unsigned decisionMaker = randomInt(engine);

    // Decide what the enemy does based on the roll, the enemies' stat's, and the amount of health remaining

    // Heal has a chance up to 30% taken by multiplying the percentage of health remaining by 30% 
    if (decisionMaker > 0 && decisionMaker <= (30 * (1-(enemy->getTempHealth() / enemy->getMaxHealth())))) {
      std::cout << "The enemy healed" << std::endl;
      enemy->heal();
    }
    // Run away has a chance up to 30% taken by the enemy's fear plus two times fear times remaining health
    else if (decisionMaker > 30 && decisionMaker < (30 + (enemy->getFear() + (2 * enemy->getFear() * (1 - enemy->getTempHealth() / enemy->getMaxHealth()))))) {
      status = Status::ENEMYRUN;
      std::cout << "The enemy ran away." << std::endl;
    }
    // 10% chance to do double damage based on the enemy's recklessness multiplied by health remaining
    else if (decisionMaker > 60 && decisionMaker < (60 + (enemy->getRecklessness() * (1 - enemy->getTempHealth() / enemy->getMaxHealth())))) {
      enemy->attack(*player);
      enemy->attack(*player);
      std::cout << "The enemy recklessly attacked, doing double damage." << std::endl;
    }
    // 10% chance to do self damage based on recklessness and current health percentage
    else if (decisionMaker > 70 && decisionMaker < (70 + enemy->getRecklessness() * (1 - enemy->getTempHealth() / enemy->getMaxHealth()))) {
      enemy->damageDealt(enemy->getStrength());
      std::cout << "The enemy recklessly attacked, but struck himself instead" << std::endl;
    }

    // otherwise the enemy just attacks you
    else {
      enemy->attack(*player);
      std::cout << "The enemy attacked you" << std::endl;
    }


    //make it be the player's turn
    turn = Turn::PLAYER;
  }

  //check to see if anyone is dead
  isDead();
  
  //display turn results if no one is dead
  if (status == Status::ATWAR) {
    turnResults();
    //press enter to continue if the player just attacked
    if (turn == Turn::ENEMY) {
      std::cin.ignore();
      std::cin.get();
    }
  }

  

}

void BattleMachine::turnResults() {
  std::cout << "Player stats:" << std::endl;
  std::cout << "Health: " << player->getTempHealth() << "/" << player->getMaxHealth() << std::endl;
  std::cout << "Mana: " << player->getMana() << std::endl;
  std::cout << "Attack: " << player->getStrength() << std::endl;
  std::cout << "\nEnemy health: " << enemy->getTempHealth() << std::endl;
}

void BattleMachine::battleResults() {
  //print results of the battle depending on what the STATUS is set to
  switch (status) {
  case PLAYERDEAD:
    std::cout << "You died. What a wimp." << std::endl;
    break;

  case PLAYERRUN:
    std::cout << "You ran away. Find some courage next time." << std::endl;
    break;

  case ENEMYDEAD:
    std::cout << "You slayed the enemy." << std::endl;
    break;

  case ENEMYRUN:
    std::cout << "You hit the enemy so hard he ran away." << std::endl;
    break;
  }

}
 
//function checks to see whether either player is dead, and updates the status
void BattleMachine::isDead() {
  if (player->getTempHealth() <= 0) {
    status = Status::PLAYERDEAD;
  }

  if (enemy->getTempHealth() <= 0) {
    status = Status::ENEMYDEAD;
  }
}
