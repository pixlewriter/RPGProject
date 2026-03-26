#include "Shop.h"
#include "InventoryItem.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <format>

using namespace std;

Node<InventoryItem>* createItem(string name, int gold, int weight) {
	return new Node<InventoryItem>(*(new InventoryItem(name, gold, weight)));
}

Shop::Shop(shopType type) {
	if (type == shopType::starter) {
		inventory.enqueue(*createItem("Basic Axe",100, 20));
		inventory.enqueue(*createItem("Basic Sword", 75, 20));
		inventory.enqueue(*createItem("Basic Dagger", 20, 15));
		inventory.enqueue(*createItem("Health Potion", 30, 5));
		inventory.enqueue(*createItem("Bread", 5, 1));
	}
	else if (type == shopType::librarian) {
		inventory.enqueue(*createItem("Physical Education 101", 100, 3));;
		inventory.enqueue(*createItem("Mechanics", 100, 3));
		inventory.enqueue(*createItem("Biology 101", 100, 3));
		inventory.enqueue(*createItem("Data Structures", 100, 3));
		inventory.enqueue(*createItem("Romeo and Juliet", 100, 3));
		inventory.enqueue(*createItem("Catechism", 10, 3));
	}
}

Shop::Shop(std::vector<InventoryItem> items) {
	for (InventoryItem item : items) {
		inventory.enqueue(*(new Node<InventoryItem>(item)));
	}
}

void Shop::addItem(InventoryItem item) {
	Node<InventoryItem> itemNode(item);
	inventory.enqueue(itemNode);
}

void Shop::removeItem(InventoryItem item) {
	Node<InventoryItem>* firstNode = inventory.getFront();
	Node<InventoryItem>* currentNode = inventory.getFront();
	do {
		if (currentNode->data == item) {
			inventory.dequeue();
			return;
		}
		else {
			Node<InventoryItem> next = *inventory.dequeue();
			inventory.enqueue(next);
		}
		currentNode = inventory.getFront();
	} while (currentNode != firstNode);
}

bool Shop::checkFor(Order order) {
	Node<InventoryItem>* firstNode = inventory.getFront();
	Node<InventoryItem>* currentNode = inventory.getFront();
	do {
		if (currentNode->data == order.item) {
			return true;
		}
		else {
			Node<InventoryItem> next = *inventory.dequeue();
			inventory.enqueue(next);
		}
		currentNode = inventory.getFront();
	} while (currentNode != firstNode);
	return false;
}

void Shop::displayStaticMenu() {
	int size = inventory.getSize();
	std::string cursor = "";
	std::string menuName = "Shop";
	cout << "--- " << menuName << " ---" << endl;
	Node<InventoryItem>* firstItem = inventory.getFront();
	Node<InventoryItem>* currentItem = inventory.getFront();
	int i = 1;
	do {
		if (firstItem==currentItem) {
			cursor = "> ";
		}
		else {
			cursor = "  ";
		}
		std::cout << "                                                                               \r";
		std::cout << cursor << i << ". " << currentItem->data.name << " ---- Cost: "<< currentItem->data.price << " ---- Weight: " << currentItem->data.weight << std::endl;
		inventory.enqueue(*inventory.dequeue());
		currentItem = inventory.getFront();
		i++;
	} while (currentItem != firstItem);
	cout << "----";
	for (int i = 0; i < menuName.size(); i++) {
		cout << "-";
	}
	cout << "----" << endl;
}

Order Shop::displayShopMenu() {
	int optionSize = inventory.getSize();
	//This string return the cursor to the start of the menu by moving the cursor up by the number of options \x1B[{number of lines + 2 (2 for the border and name)}A
//then return the cursor to the start of the line \r
	std::string returnString = std::format("\x1B[{}A\r", optionSize + 2);
	displayStaticMenu();

	while (true) {
		if (_kbhit()) { // Check if a key has been pressed
			char key = _getch(); // Get the key character
			if (key == -32 || key == 0) {
				key = _getch();
				switch (key) {
				case 80:
					inventory.enqueue(*inventory.dequeue());
					std::cout << returnString;
					std::cout << "                                                                               \r";
					displayStaticMenu();
					break;
				default:
					break;
				}
			}
			else if (key == 13) {
				int amount;
				cout << inventory.getFront()->data.name << " x";
				cin >> amount;
				Order order;
				order.item = inventory.getFront()->data;
				order.number = amount;
				return order;
			}

		}
	}
	Order nullOrder;
	nullOrder.item = InventoryItem("null", 0, 0);
	nullOrder.number = 0;
	return nullOrder;
}