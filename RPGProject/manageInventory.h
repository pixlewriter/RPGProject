#pragma once
#include "Player.h"
#include "InventoryItem.h"
#include<iostream>
#include<list>
#include<algorithm>


inline void printInventory(std::list<InventoryItem> inventory) {
  for (InventoryItem item : inventory) {
    if (item.amount > 0) 
      std::cout << item.name << ": " << item.amount;
  }
}


//this function takes in an inventory and a string and increments the counter 
inline void addItem(std::list<InventoryItem>& inventory, std::string name) {
  auto iterator = std::find_if(inventory.begin(), inventory.end(), [name](const InventoryItem& check) {return check.name == name; });

  iterator->amount++;
}

//this function takes in an inventory and an item name as arguemnts
//it finds the item and decrements the counter if the counter is greater than zero
inline void removeItem(std::list<InventoryItem>& inventory, std::string name) {
  auto iterator = std::find_if(inventory.begin(), inventory.end(), [name](const InventoryItem& check) {return check.name == name; });

  if (iterator->amount>0) {
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

   switch (choice) {
   case '1':
     printInventory(player->inventory);
     break;

   case'2':
     std::cout << "You picked up a rock" << std::endl;
     addItem(player->inventory, "Rock");
     printInventory(player->inventory);
     break;

   case '3':
     std::cout << "You dropped a rock" << std::endl;
     removeItem(player->inventory, "Rock");
     printInventory(player->inventory);
     break;
   }
}

