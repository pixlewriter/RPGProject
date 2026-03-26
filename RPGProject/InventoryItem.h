#pragma once
#include<string>
#include<list>

//inventory item class, containin constructor and members price and name
struct InventoryItem {
  InventoryItem(std::string n, int p, int w) : name(n), price(p), weight(w) {}

  int amount = 0;
  std::string name;
  int price;
  int weight;

  bool operator==(const InventoryItem& other) const {
      return name == other.name;
  }
};


//generates the inventory, with is set with default values of 0 for all items
/*inline std::list<InventoryItem> generateInventory() {
  std::list<InventoryItem> inventory{
    {"Key", 100, 5},
    {"Gold Nugget", 300, 30},
    {"Emerald", 700, 25},
    {"Diamond", 1000, 10},
    {"Rock", 10, 50},
    {"Coin", 50, 1}
  };
  return inventory;
}*/
