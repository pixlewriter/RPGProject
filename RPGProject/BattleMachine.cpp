#include<iostream>
#include<random>
#include<string>
#include<ctime>
#include "BattleMachine.h"
#include "Character.h"
#include "Enemy.h"
#include "Player.h"
#include "audio_manager.h"

using namespace std;

//creates a new battle, spawning the player and a random enemy

BattleMachine::BattleMachine(Character* player) {
  //Spawns the player and sets stats
  Enemy* newEnemy = nullptr;

  //pick a random number between 1 and 3 to determine which enemy to generate
  default_random_engine engine{ static_cast<unsigned>(time(0)) };
  uniform_int_distribution<unsigned> randomInt{ 1,3 };
  unsigned decisionMaker = randomInt(engine);

  //a switch statement to decide which enemy to generate
  switch (decisionMaker) {

  case 1:
    //generated a alien worker
    newEnemy = alienWorker();
    break;

  case 2:
    //generate a alien soldier
    newEnemy = alienSolier();
    break;

  case 3:
    //generate an intergalactic technician
    newEnemy = intergalacticTechnician();
    break;
  }

  this->enemy = newEnemy;
  this->player = player;
}
void BattleMachine::takeTurn() {
  //allows the player to go if it is players turn
  if (turn == Turn::PLAYER) {
    //diplay a menu
    cout << "Make your move. Choose wisely." << endl;
    cout << "1. Attack" << endl;
    cout << "2. Heal" << endl;
    cout << "3. Run away" << endl;
    char choice;
    cin >> choice;

    //input validation, in case the user enters something different
    while (choice != '1' && choice != '2' && choice != '3') {
      cin >> choice;
    }

    cout << "\033[2J\033[1;1H";

    switch (choice) {
    case '1':
      //player attacks the enemy
      player->attack(*enemy);

      play_effect("attack_example_sound.wav");
      
      cout << "You attacked the enemy" << endl;
      break;

    case '2':
      //player heals
      player->heal();
      cout << "You healed" << endl;
      break;

    case '3':
      //player runs away
      status = Status::PLAYERRUN;
      break;
    }

    //change the turn
    turn = Turn::ENEMY;
  }
  
  //otherwise the enemy goes
  else {
    cout << "\033[2J\033[1;1H";
   //pick a random number between 1 and 100 to determine enemy move
    default_random_engine engine{ static_cast<unsigned>(time(0)) };
    uniform_int_distribution<unsigned> randomInt{ 1,100 };
    unsigned decisionMaker = randomInt(engine);

    // Decide what the enemy does based on the roll, the enemies' stat's, and the amount of health remaining

    // Heal has a chance up to 30% taken by multiplying the percentage of health remaining by 30% 
    if (decisionMaker > 0 && decisionMaker <= (30 * (1-(enemy->getTempHealth() / enemy->getMaxHealth())))) {
      cout << "The enemy healed" << endl;
      enemy->heal();
    }
    // Run away has a chance up to 30% taken by the enemy's fear plus two times fear times remaining health
    else if (decisionMaker > 30 && decisionMaker < (30 + (enemy->getFear() + (2 * enemy->getFear() * (1 - enemy->getTempHealth() / enemy->getMaxHealth()))))) {
      status = Status::ENEMYRUN;
      cout << "The enemy ran away." << endl;
    }
    // 10% chance to do double damage based on the enemy's recklessness multiplied by health remaining
    else if (decisionMaker > 60 && decisionMaker < (60 + (enemy->getRecklessness() * (1 - enemy->getTempHealth() / enemy->getMaxHealth())))) {
      enemy->attack(*player);
      enemy->attack(*player);
      cout << "The enemy recklessly attacked, doing double damage." << endl;
    }
    // 10% chance to do self damage based on recklessness and current health percentage
    else if (decisionMaker > 70 && decisionMaker < (70 + enemy->getRecklessness() * (1 - enemy->getTempHealth() / enemy->getMaxHealth()))) {
      enemy->damageDealt(enemy->getStrength());
      cout << "The enemy recklessly attacked, but struck himself instead" << endl;
    }

    // otherwise the enemy just attacks you
    else {
      enemy->attack(*player);
      cout << "The enemy attacked you" << endl;
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
      cin.ignore();
      cin.get();
    }
  }

  

}

void BattleMachine::turnResults() {
  cout << "Player stats:" << endl;
  cout << "Health: " << player->getTempHealth() << "/" << player->getMaxHealth() << endl;
  cout << "Mana: " << player->getMana() << endl;
  cout << "Attack: " << player->getStrength() << endl;
  cout << "\nEnemy health: " << enemy->getTempHealth() << endl;
}

void BattleMachine::battleResults() {
  //print results of the battle depending on what the STATUS is set to
  switch (status) {
  case PLAYERDEAD:
    cout << "You died. What a wimp." << endl;
    break;

  case PLAYERRUN:
    cout << "You ran away. Find some courage next time." << endl;
    break;

  case ENEMYDEAD:
    cout << "You slayed the enemy." << endl;
    break;

  case ENEMYRUN:
    cout << "You hit the enemy so hard he ran away." << endl;
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
