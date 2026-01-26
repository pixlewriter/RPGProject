#include "Player.h"
#include "Character.h"
#include "Enemy.h"

void Player::attack(Character& character) {
	double dmg = getStrength();
	character.damageDealt(dmg);
}

void Player::heal() {
	heal();
}

void damageDelt(double damage) {
	damageDelt(damage);
}