#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <array>

namespace QOLL {

	enum class STYLE { NONE = 0, BOLD = 1, UNDERLINE = 4, BLINK = 5, INVERSE = 7 };
	enum class FGCOLOR { NONE = 0, BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
	enum class BGCOLOR { NONE = 0, BLACK = 40, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

	struct Color {
		STYLE style = STYLE::NONE;
		FGCOLOR fGColor = FGCOLOR::NONE;
		BGCOLOR bGColor = BGCOLOR::NONE;
	};


	template <typename T>
	void printVector(std::vector<T>& items, std::string seperator = ",", std::string ending = "") {
		//Print each item in the vector
		int i = 0;
		for (T item : items) {
			i++;
			if (i >= items.size()) {
				break;
			}
			std::cout << item << seperator;
		}
		std::cout << items[items.size() - 1] << ending << std::endl;
	}

	template <typename T, int S>
	void printArray(std::array<T, S>& items, std::string seperator = ",", std::string ending = "") {
		//Print each item in the vector
		int i = 0;
		for (T item : items) {
			i++;
			if (i >= items.size()) {
				break;
			}
			std::cout << item << seperator;
		}
		std::cout << items[items.size() - 1] << ending << std::endl;
	}

	template <typename T>
	void multiplyElements(int factor, std::vector<T>& items) {
		for (int i = 0; i < items.size(); i++) {
			items[i] *= factor;
		}
	}

	int getRandomNum(int min, int max);
	std::string stringToLower(std::string text);
	int rollDice(int num, std::string dice);
	std::string validateAnswer(std::string question, std::vector<std::string> answers); //TODO Overload with Regex's?
	int validateAnswer(std::string question, int start, int end);
	std::string colorText(Color color);
	std::string colorText(std::string text, Color color, bool end = true);
	std::string center(std::string text, unsigned int width);
	std::string center(std::string text, unsigned int width, Color color);
	void printMenu(int currentChoice, const char* options[], const int optionsSize);
	int menuInput(const char* options[], const int optionSize);

}
