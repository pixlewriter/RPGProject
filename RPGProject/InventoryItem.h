#pragma once
#include<string>
#include<list>

//inventory item class, containin constructor and members price and name
struct InventoryItem {
  InventoryItem(std::string n, int p) : name(n), price(p) {}

  int amount = 0;
  std::string name;
  int price;
};


//generates the inventory, with is set with default values of 0 for all items
inline std::list<InventoryItem> generateInventory() {
  std::list<InventoryItem> inventory{
    {"Key", 100},
    {"Gold Nugget", 300},
    {"Emerald", 700},
    {"Diamond", 1000},
    {"Rock", 10},
    {"Coin", 50}
  };
  return inventory;
}
