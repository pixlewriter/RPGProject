#pragma once
#include "Player.h"
#include "InventoryItem.h"
#include<iostream>
#include<list>
#include<algorithm>


inline void printInventory(const std::list<InventoryItem>& inventory) {
  for (const InventoryItem& item : inventory) {
    if (item.amount > 0) {
      std::cout << item.name << ": " << item.amount << std::endl;
    }
  }
  std::cout << std::endl;
}


//this function takes in an inventory and a string and increments the counter 
inline void addItem(std::list<InventoryItem>& inventory, std::string name) {
  auto iterator = std::find_if(inventory.begin(), inventory.end(), [name](const InventoryItem& check) {return check.name == name; });
  if (iterator != inventory.end()) {
    iterator->amount++;
  }
  else {
    InventoryItem newItem(name, 0);
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

inline void manageInventory(Character* player) {
   //diplay a menu for the player to choose
   std::cout << "Select an option" << std::endl;
   std::cout << "1. View Inventory" << std::endl;
   std::cout << "2. Add item" << std::endl;
   std::cout << "3. Drop item" << std::endl;
   char choice;
   std::cin >> choice;

   //input validation, in case the user enters something different
   while (choice != '1' && choice != '2' && choice != '3') {
     std::cin >> choice;
   }

   std::cout << "\033[2J\033[1;1H";

   std::list<InventoryItem>& inventory = player->getInventory();

   switch (choice) {
   case '1':
     printInventory(inventory);
     break;

   case'2':
     std::cout << "You picked up a rock" << std::endl;
     addItem(inventory, "Rock");
     printInventory(inventory);
     break;

   case '3':
     std::cout << "You dropped a rock" << std::endl;
     removeItem(inventory, "Rock");
     printInventory(inventory);
     break;
   }
}

