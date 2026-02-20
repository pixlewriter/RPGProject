#include <vector>
#include <string>

#pragma once
class IntegerChangeMenu
{
	std::vector<int> values;
	std::vector<std::string> names;

	
public:
	void printMenuPhase(int);
	void printMenu(int);
	std::vector<int> getValues();
	IntegerChangeMenu(std::vector<int> &defaultValues, std::vector<std::string> names) : values{ defaultValues }, names{ names } {
		if (values.size() < names.size()) {
			for (int i = 0; i < (names.size() - values.size()); i++) {
				values.push_back(0);
			}
		}
	}


};

