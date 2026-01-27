#include<iostream>
#include<random>
#include<string>
#include<ctime>
#include "BattleMachine.h"
#include "Character.h"
#include "Enemy.h"
#include "Player.h"

using namespace std;

//creates a new battle, spawning the player and a random enemy

BattleMachine::BattleMachine() {
  //Spawns the player and sets stats
  Character* newPlayer = new Player(50,10,10);
  Character* newEnemy = nullptr;

  //pick a random number between 1 and 3 to determine which enemy to generate
  default_random_engine engine{ static_cast<unsigned>(time(0)) };
  uniform_int_distribution<unsigned> randomInt{ 1,3 };
  unsigned decisionMaker = randomInt(engine);

  //a switch statement to decide which enemy to generate
  switch (decisionMaker) {

  case 1:
    //generated a troll
    newEnemy = new Enemy(100, 5, 0);
    cout << "A wild troll appears. It's tough but slow." << endl;
    break;

  case 2:
    //generate a ghost
    newEnemy = new Enemy(10, 10, 10);
    cout << "It's a ghost. It looks pretty fragile." << endl;
    break;

  case 3:
    //generate a witch
    newEnemy = new Enemy(25, 15, 25);
    cout << "A witch. Burn her." << endl;
    break;
  }

  this->enemy = newEnemy;
  this->player = newPlayer;
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
   //pick a random number between 1 and 5 to determine enemy move
    default_random_engine engine{ static_cast<unsigned>(time(0)) };
    uniform_int_distribution<unsigned> randomInt{ 1,5 };
    unsigned decisionMaker = randomInt(engine);

    switch (decisionMaker) {
    case 1:
    case 2:
    case 3:
     //enemy attackes the player
      enemy->attack(*player);
      cout << "The enemy attacked you" << endl;
      break;

    case 4:
      //enemy heals
      enemy->heal();
      cout << "The enemy healed" << endl;
      break;

    case 5:
      //enemy runs away
      status = Status::ENEMYRUN;
      break;
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
