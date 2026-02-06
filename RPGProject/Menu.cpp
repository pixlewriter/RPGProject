#include "Menu.h"
#include <conio.h>
#include <iostream>
#include <format>


using namespace std;

void Menu::printStaticMenu(int currentChoice = -1) {
	int size = options.size();
	std::string cursor = "";
	cout << "--- " << menuName << " ---" << endl;
	for (int i = 1; i < size + 1; i++) {
		if (currentChoice == i) {
			cursor = "> ";
		}
		else {
			cursor = "- ";
		}
		std::cout << cursor << i << ". " << options[i - 1] << std::endl;

	}
	cout << "----";
	for (int i = 0; i < menuName.size(); i++) {
		cout << "-";
	}
	cout << "----" << endl;
}

int Menu::printDynamicMenu() {
	int optionSize = options.size();
	//This string return the cursor to the start of the menu by moving the cursor up by the number of options \x1B[{number of lines + 2 (2 for the border and name)}A
//then return the cursor to the start of the line \r
	std::string returnString = std::format("\x1B[{}A\r", optionSize+2);
	int currentChoice = 1;
	printStaticMenu(currentChoice);

	while (true) {
		if (_kbhit()) { // Check if a key has been pressed
			char key = _getch(); // Get the key character
			if (key == -32 || key == 0) {
				key = _getch();
				switch (key) {
				case 80:
					currentChoice = ((currentChoice++) % optionSize) + 1;
					std::cout << returnString;
					printStaticMenu(currentChoice);
					break;
				case 72:
					if (currentChoice <= 1) currentChoice = optionSize;
					else currentChoice--;
					std::cout << returnString;
					printStaticMenu(currentChoice);
					break;
				default:
					break;
				}
			}
			else if (key == 13) {
				return currentChoice;
			}

		}
	}
	return 0;
}

string Menu::getMenuName() {
	return menuName;
}

void Menu::setMenuName(string name) {
	menuName = name;
}