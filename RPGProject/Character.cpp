#include "Character.h"

void Character::attack(Character& character) {
	character.damageDealt(getStrength());
}

void Character::heal() {
	int amt = 5;
	setTempHealth(getTempHealth() + amt);
	setMana(getMana() - amt);
}

void Character::damageDealt(double damage) {
	setTempHealth(getTempHealth() - damage);
}

double Character::getStrength() {
	return strength;
}

void Character::setStrength(double dmg) {
	strength = dmg;
}

double Character::getTempHealth() {
	return tempHealth;
}

void Character::setTempHealth(double hitPoints) {
	if (hitPoints <= 0) {
		hitPoints = 1;
	}
	tempHealth = hitPoints;
}

double Character::getMaxHealth() {
	return maxHealth;
}

void Character::setMaxHealth(double hitPoints) {
	maxHealth = hitPoints;
}

double Character::getMana() {
	return mana;
}

void Character::setMana(double mana) {
	this->mana = mana;
}