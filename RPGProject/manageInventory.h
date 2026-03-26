#pragma once
#include "Player.h"
#include "Menu.h"
#include "InventoryItem.h"
#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<algorithm>




//this function takes in an inventory and a string and increments the counter 
/*inline void addItem(std::list<InventoryItem>& inventory, InventoryItem& item) {
  auto iterator = std::find_if(inventory.begin(), inventory.end(), [item.name](const InventoryItem& check) {return check.name == item.name; });
  if (iterator != inventory.end()) {
    if (item.weight + )
    iterator->amount++;
  }
  else {
    InventoryItem newItem(item.name, item.price, item.weight);
    newItem.amount = 1;
    inventory.push_back(newItem);
  }
}

//this function takes in an inventory and an item name as arguemnts
//it finds the item and decrements the counter if the counter is greater than zero
inline void removeItem(std::list<InventoryItem>& inventory, std::string name) {
  auto iterator = std::find_if(inventory.begin(), inventory.end(), [name](const InventoryItem& check) {return check.name == name; });
  if (iterator != inventory.end() && iterator->amount > 0) {
    iterator->amount--;
  }
}
*/

inline void manageInventory(Player* player) {
  //display the player's inventory
  player->printInventory();
  std::cout << std::endl;

  //diplay a menu for the player to choose
  std::vector<std::string> options{ "Drop item", "Return to menu" };
  ListMenu checkInventory("Inventory Management", options);
  int inventoryChoice = 0;

  while (inventoryChoice != 2) {
    inventoryChoice = checkInventory.printDynamicMenu();
    if (inventoryChoice == 1)
      player->dropItem();
    }
  }

