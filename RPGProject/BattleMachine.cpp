#include<iostream>
#include<random>
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

  //pick a random number between 1 and 10 to determine which enemy to generate
  default_random_engine engine{ static_cast<unsigned>(time(0)) };
  uniform_int_distribution<unsigned> randomInt{ 1,10 };
  unsigned decisionMaker = randomInt(engine);

  //a switch statement to decide which enemy to generate
  switch (decisionMaker) {

  case 1:
  case 2:
  case 3:
    //generated a troll
    newEnemy = new Enemy(100, 5, 0);
    cout << "A wild troll appears. It's tough but slow." << endl;
    break;

  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
    //generate a ghost
    newEnemy = new Enemy(10, 10, 10);
    cout << "It's a ghost. It looks pretty fragile." << endl;
    break;

  case 9:
  case 10:
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
    //player attacks the enemy
    player->attack(*enemy);
    cout << "You attacked the enemy" << endl;
    //change the turn
    turn = Turn::ENEMY;
    cin.ignore();
  }
  //otherwise the enemy goes
  else {
    //enemy attackes the player
    enemy->attack(*player);
    cout << "The enemy attacked you" << endl;
    //make it be the player's turn
    turn = Turn::PLAYER;
    cin.ignore();
  }
  turnResults();
}

void BattleMachine::turnResults() {
  cout << "An attack was made" << endl;
  cout << "Player stats:" << endl;
  cout << "Health: " << player->getTempHealth() << "/" << player->getMaxHealth() << endl;
  cout << "Mana: " << player->getMana() << endl;
  cout << "Attack: " << player->getStrength() << endl;
  cout << "\nEnemy health: " << enemy->getTempHealth() << endl;
}

void BattleMachine::battleResults() {
  cout << "The battle is over" << endl;
}
 
