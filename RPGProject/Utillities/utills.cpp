#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random>
#include <format>
#include <stdio.h>
#include <conio.h>
#include "utills.h"

namespace QOLL {
	std::string stringToLower(std::string text) {
		for (char& character : text) {
			character = tolower(character);
		}
		return text;
	}

	int getRandomNum(int min, int max) {
		std::random_device rd;
		std::mt19937 engine(rd());

		std::uniform_int_distribution<int> dist(min, max);

		return dist(engine);
	}

	int rollDice(int num, std::string dice) {
		dice = stringToLower(dice);
		if (dice == "d4") return getRandomNum(num, num * 4);
		else if (dice == "d6") return getRandomNum(num, num * 6);
		else if (dice == "d8") return getRandomNum(num, num * 8);
		else if (dice == "d10") return getRandomNum(num, num * 10);
		else if (dice == "d12") return getRandomNum(num, num * 12);
		else if (dice == "d20") return getRandomNum(num, num * 20);
		else if (dice == "d100") return getRandomNum(num, num * 100);
		else return 0;
	}

	std::string validateAnswer(std::string question, std::vector<std::string> answers) {
		std::string input;
		bool answerFound = false;
		std::cout << question << ": ";
		std::getline(std::cin >> std::ws, input);
		for (std::string answer : answers) {
			if (input == answer) {
				answerFound = true;
			}
		}
		while (!answerFound) {
			std::cout << "No I asked \"" << question << "\" ";
			std::cin >> input;
			for (std::string answer : answers) {
				if (input == answer) {
					answerFound = true;
				}
			}
		}
		return input;

	}
	int validateAnswer(std::string question, int start, int end) {
		std::string input;
		bool answerFound = false;
		std::cout << question << ": ";
		std::getline(std::cin >> std::ws, input);
		for (int i = start; i <= end; i++) {
			if (input == std::to_string(i)) {
				answerFound = true;
			}
		}
		while (!answerFound) {
			std::cout << "No I asked \"" << question << "\" ";
			std::cin >> input;
			for (int i = start; i <= end; i++) {
				if (input == std::to_string(i)) {
					answerFound = true;
				}
			}
		}
		return std::stoi(input);

	}


	std::string colorText(Color color) {
		std::string s = std::to_string(static_cast<int>(color.style));
		std::string f = std::to_string(static_cast<int>(color.fGColor));
		std::string b = std::to_string(static_cast<int>(color.bGColor));

		std::string output = "\033[";
		output += (s == "0" ? "" : s);
		output += (f != "0" || b != "0" ? ";" : "");
		output += (f == "0" ? "" : f);
		output += (b != "0" ? ";" : "");
		output += (b == "0" ? "" : b);
		output += "m";

		return output;
	}

	std::string colorText(std::string text, Color color, bool end) {
		std::string s = std::to_string(static_cast<int>(color.style));
		std::string f = std::to_string(static_cast<int>(color.fGColor));
		std::string b = std::to_string(static_cast<int>(color.bGColor));
		
		std::string output = "\033[";
		output += (s == "0" ? "" : s);
		output += (f != "0" || b != "0" ? ";" : "");
		output += (f == "0" ? "" : f);
		output += (b != "0" ? ";" : "");
		output += (b == "0" ? "" : b);
		output += "m";
		output += text;
		output += (end ? "\033[0m" : "");

		return output;
	}

	std::string center(std::string text, unsigned int width) {
		std::string output = "";
		//bool textOdd = text.length() % 2;
		//bool widthOdd = text.length() % 2;
		if (text.length() == width) {
			return text;
		}
		if (text.length() > width) {
			for (int i = 0; i <= width; i++) {
				output += text[i];
			}
			return output;
		}

		size_t padding = (width - text.length()) / 2;
		for (int i = 0; i < padding; i++) {
			output += ' ';
		}
		int diff = width - text.length();
		if (diff % 2 == 1) {
			output += ' ';
		}
		output += text;
		for (int i = 0; i < padding; i++) {
			output += ' ';
		}


		return output;
	}

	std::string center(std::string text, unsigned int width, Color color) {
		std::string output = "";
		//bool textOdd = text.length() % 2;
		//bool widthOdd = text.length() % 2;
		if (text.length() == width) {
			return colorText(text,color,true);
		}
		if (text.length() > width) {
			for (int i = 0; i <= width; i++) {
				output += colorText(""+text[i], color, true);
			}
			return output;
		}

		size_t padding = (width - text.length()) / 2;
		for (int i = 0; i < padding; i++) {
			output += ' ';
		}
		int diff = width - text.length();
		if (diff % 2 == 1) {
			output += ' ';
		}
		output += colorText(text,color,true);
		for (int i = 0; i < padding; i++) {
			output += ' ';
		}


		return output;
	}

	void printMenu(int currentChoice, const char* options[], const int size) {
		std::string cursor = "";
		for (int i = 1; i < size + 1; i++) {
			if (currentChoice == i) {
				cursor = "> ";
			}
			else {
				cursor = "- ";
			}
			std::cout << cursor << i << ". " << options[i - 1] << std::endl;

		}
	}

	int menuInput(const char* options[], const int optionSize) {
		//This string return the cursor to the start of the menu by moving the cursor up by the number of options \x1B[{number of lines}A
	//then return the cursor to the start of the line \r
		std::string returnString = std::format("\x1B[{}A\r",optionSize);
		int currentChoice = 1;
		printMenu(currentChoice, options, optionSize);

		while (true) {
			if (_kbhit()) { // Check if a key has been pressed
				char key = _getch(); // Get the key character
				if (key == -32 || key == 0) {
					key = _getch();
					switch (key) {
					case 72:
						currentChoice = ((currentChoice++) % optionSize) + 1;
						std::cout << returnString;
						printMenu(currentChoice, options, optionSize);
						break;
					case 80:
						if (currentChoice <= 1) currentChoice = optionSize;
						else currentChoice--;
						std::cout << returnString;
						printMenu(currentChoice, options, optionSize);
						break;
					default:
						break;
					}
				}
				else if (key == 13) {
					return currentChoice;
				}
				else {
					std::cout << key << "=" << (int)key << std::endl;
				}

			}
		}
		return 0;
	}
}
