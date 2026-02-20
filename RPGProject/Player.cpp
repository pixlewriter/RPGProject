#include "Player.h"
#include "Character.h"
#include "Enemy.h"
#include "IntegerChangeMenu.h"

using namespace std;

void Player::attack(Character& character) {
	double dmg = getStrength();
	character.damageDealt(dmg);
}

void Player::heal() {
	Character::heal();
}

void Player::damageDealt(double damage) {
	Character::damageDealt(damage);
}

void Player::updateStats() {
	double health = constitution * 10 + dexterity * 5;
	double tempHealthIncrease = health - getMaxHealth();
	setMaxHealth(health);
	setTempHealth(getTempHealth() + tempHealthIncrease);

	double attack = strength * 5 + dexterity * 2.5;
	setStrength(attack);

	double mana = intelligence * 10 + wisdom * 5;
	setMana(mana);
}

void Player::increaseStat(ABBILITY abb, int num) {
	switch (abb) {
	case 6:
	case 0:
		strength += num;
		if (abb != ABBILITY::all) {
			break;
		}
	case 1: 
		dexterity += num;
		if (abb != ABBILITY::all) {
			break;
		}
	case 2:
		constitution += num;
		if (abb != ABBILITY::all) {
			break;
		}
	case 3:
		intelligence += num;
		if (abb != ABBILITY::all) {
			break;
		}
	case 4:
		wisdom += num;
		if (abb != ABBILITY::all) {
			break;
		}
	case 5:
		constitution += num;
		if (abb != ABBILITY::all) {
			break;
		}
	}
	updateStats();
}

int Player::getStat(ABBILITY abb) {
	switch (abb) {
	case 0:
		return strength;
	case 1:
		return dexterity;
	case 2:
		return constitution;
	case 3:
		return intelligence;
	case 4:
		return wisdom;
	case 5:
		return charisma;
	}
}

void Player::generateStats(int points) {
	vector<int> values = { 0,0,0,0,0,0 };
	for (int i = 0; i < 6; i++) {
		vector<int> roles = { QOLL::rollDice(1, "d6") };
		int lowest = 0;
		for (int j = 1; j < 4; j++) {
			roles.push_back(QOLL::rollDice(1, "d6"));
			if (roles[lowest] > roles[j]) {
				lowest = j;
			}
		}
		roles.erase(roles.begin() + lowest);
		int value = 0;
		for (int role : roles) {
			values[i] += role;
		}
	}
	vector<string> names = { "str", "dex", "con", "int", "wis", "cha" };
	IntegerChangeMenu statMenu = { values, names };
	statMenu.printMenu(points);
	values = statMenu.getValues();
	strength = values[0];
	dexterity = values[1];
	constitution = values[2];
	intelligence = values[3];
	wisdom = values[4];
	charisma = values[5];
}

void Player::printStats() {
	cout << strength << ", ";
	cout << dexterity << ", ";
	cout << constitution << ", ";
	cout << intelligence << ", ";
	cout << wisdom << ", ";
	cout << charisma << endl;
}
