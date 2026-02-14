#pragma once
#include "Player.h"
#include "InventoryItem.h"
#include<iostream>
#include<list>
#include<algorithm>

inline void manageInventory(Player* player) {
  /*
   //diplay a menu for the player to choose
   std::cout << "Select an option" << std::endl;
   std::cout << "1. View Inventory" << std::endl;
   std::cout << "2. Add item" << std::endl;
   std::cout << "3. Drop item" << std::endl;
   std::cout << "4. Exit" << std::endl;
   char choice;
   std::cin >> choice;

   //input validation, in case the user enters something different
   while (choice != '1' && choice != '2' && choice != '3' && choice != '4') {
     std::cin >> choice;
   }

   std::cout << "\033[2J\033[1;1H";
   */

}

void printInventory(std::list<InventoryItem> inventory) {
  for (InventoryItem item : inventory) {
    if (item.amount > 0) 
      std::cout << item.name << ": " << item.price;
  }
}


//this function takes in an inventory and a string and increments the counter 
void addItem(std::list<InventoryItem>& inventory, std::string name) {
  auto iterator = std::find_if(inventory.begin(), inventory.end(), [name](const InventoryItem& check) {return check.name == name; });

  iterator->amount++;
}

//this function takes in an inventory and an item name as arguemnts
//it finds the item and decrements the counter if the counter is greater than zero
void removeItem(std::list<InventoryItem>& inventory, std::string name) {
  auto iterator = std::find_if(inventory.begin(), inventory.end(), [name](const InventoryItem& check) {return check.name == name; });

  if (iterator->amount>0) {
    iterator->amount--;
  }
}
