#include "Enemy.h"

void Enemy::damageDealt(double damage) {
	Character::damageDealt(damage);
	if (damage > 10) {
		fear += 5;
	}
	recklessness = 1 - (getTempHealth() / getMaxHealth());
}