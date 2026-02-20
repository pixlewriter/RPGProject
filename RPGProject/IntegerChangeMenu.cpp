#include "integerChangeMenu.h"
#include "Utillities/utills.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <format>

using namespace std;

void IntegerChangeMenu::printMenuPhase(int currentChoice) {
	int charLineCount = 0;
	for (int i = 0; i < names.size();i++) {
		string name = names[i];
		if (i+1 == currentChoice) {
			QOLL::Color highlight;
			highlight.bGColor = QOLL::BGCOLOR::WHITE;
			highlight.fGColor = QOLL::FGCOLOR::BLACK;
			cout << QOLL::center("+", name.size() + 2,highlight);
		}
		else {
			cout << QOLL::center("+", name.size() + 2);
		}
		charLineCount += name.size() + 2;
	}
	cout << endl;
	cout << endl;
	for (int i = 0; i < names.size(); i++) {
		cout << QOLL::center(to_string(values[i]), names[i].size() + 2);
	}
	cout << endl;
	for (std::string name : names) {
		cout << QOLL::center(name, name.size() + 2);
	}
	cout << endl;
	cout << endl;
	for ( int i = 0; i < names.size(); i++) {
		string name = names[i];
		if (i+1+names.size() == currentChoice) {
			QOLL::Color highlight;
			highlight.bGColor = QOLL::BGCOLOR::WHITE;
			highlight.fGColor = QOLL::FGCOLOR::BLACK;
			cout << QOLL::center("-", name.size() + 2, highlight);
		}
		else {
			cout << QOLL::center("-", name.size() + 2);
		}
		charLineCount += name.size() + 2;
	}
	cout << endl;
}

void IntegerChangeMenu::printMenu(int points) {
	int optionSize = values.size();
	const vector<int> mins = values;
	std::string returnString = std::format("\x1B[{}A\r", 7);
	int currentChoice = 1;
	cout << "Points left: " << points << "      " << endl;
	printMenuPhase(currentChoice);

	enum direction {NO,UP,DOWN,LEFT,RIGHT };

	while (points>0) {
		if (_kbhit()) {
			direction dir = NO;
			char key = _getch();
			if (key == -32 || key == 0) {
				key = _getch();
				switch (key) {
				case 72:
					dir = direction::UP;
					break;
				case 80:
					dir = direction::DOWN;
					break;
				case 75:
					dir = direction::LEFT;
					break;
				case 77:
					dir = direction::RIGHT;
					break;
				default:
					break;
				}
			}
			else if (key == 13) {
				int index = ((currentChoice-1) % (values.size()));
				if(currentChoice <= values.size()){
					values[index]++;
					points--;
				}
				else {
					if (values[index] - 1 >= mins[index]) {
						values[index]--;
						points++;
					}
				}

			}
			if (dir == direction::UP || key == 119) {
				//cout << "UP: 119" << endl;
				currentChoice += values.size();
				if (currentChoice > values.size() * 2) {
					currentChoice -= values.size() * 2;
				}
			}
			else if (dir == direction::DOWN || key == 115) {
				//cout << "DOWN: 115" << endl;
				currentChoice -= values.size();
				if (currentChoice < 1) {
					currentChoice += values.size() * 2;
				}
			}
			else if (dir == direction::LEFT || key == 97) {
				//cout << "LEFT: 97" << endl;
				currentChoice--;
				if (currentChoice <= 0) {
					currentChoice = values.size() * 2;
				}
			}
			else if (dir == direction::RIGHT || key == 100) {
				//cout << "RIGHT: 100" << endl;
				currentChoice = (currentChoice++) % (values.size() * 2) + 1;
			}
			std::cout << returnString;
			cout << "Points left: " << points << "      " << endl;
			printMenuPhase(currentChoice);
		}
	}
}

vector<int> IntegerChangeMenu::getValues() {
	return values;
}