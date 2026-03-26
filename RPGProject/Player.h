#pragma once
#include "Character.h"
#include "Utillities/utills.h"
#include "Shop.h";
#include "InventoryItem.h"

class Player :
    public Character
{
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    int luck;
    int level;
    int gold = 500;
    int inventoryWeight = 0;
    using Character::Character;
public:
    static enum ABBILITY {str,dex,con,inte,wis,chars,all};
    Player(int str, int dex, int con, int inte, int wis, int chars) :
    strength{ str },
    dexterity{ dex },
    constitution{ con },
    intelligence{ inte },
    wisdom{ wis },
    charisma{ chars },
    luck{ QOLL::getRandomNum(1,20)},
    level{ 1 } {
        int health = level * (constitution + luck);
        int attack = level * ((strength + luck) / 2);
        int spellAbility = (intelligence > wisdom ? intelligence : wisdom);
        int mana = 10 * level * spellAbility;
        Character(health, attack, mana);
    }
    void attack(Character& character) override;
    void heal() override;
    void damageDealt(double damage) override;
    void updateStats();
    void increaseStat(ABBILITY, int);
    int getStat(ABBILITY);
    void generateStats(int points);
    void printStats();
    void dropItem();
    void addToInventory(InventoryItem);
    std::list<InventoryItem>& getInventory();
    bool purchaseOrder(Order);
    void printInventory();
    int seeGold() { return gold; }
    int seeWeight() { return inventoryWeight; }
};


