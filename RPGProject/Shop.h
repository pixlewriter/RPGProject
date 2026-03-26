#include "InventoryItem.h"
#include "Utillities/structures.h"
#include <vector>
#pragma once

struct Order {
    // Initialize `item` with an explicit InventoryItem so Order has a valid default constructor.
    InventoryItem item = InventoryItem("", 0, 0);
    int number = 0;

    // Defaulted default constructor (now available because members have default initializers)
    Order() = default;

    // Convenience constructor
    Order(const InventoryItem& it, int num) : item(it), number(num) {}
};

enum shopType { starter, librarian };

class Shop
{
    Queue<InventoryItem> inventory;
    void displayStaticMenu();
public:
    Shop(shopType);
    Shop(std::vector<InventoryItem>);
    Order displayShopMenu();
    void addItem(InventoryItem);
    void removeItem(InventoryItem);
    bool checkFor(Order);
};

