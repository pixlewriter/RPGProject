#include "Enemy.h"

void Enemy::damageDealt(double damage) {
	Character::damageDealt(damage);
	if (damage > 10) {
		fear += 5;
	}
	recklessness = 1 - (getTempHealth() / getMaxHealth());
}

int Enemy::getFear() {
	return fear;
}

int Enemy::getRecklessness (){
	return recklessness;
}

void Enemy::setFear(int num) {
	fear = num;
}

void Enemy::setRecklessness(int num) {
	recklessness = num;
}