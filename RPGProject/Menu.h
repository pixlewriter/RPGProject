#include <vector>
#include <string>
#pragma once
class ListMenu
{
private:
	std::vector<std::string> options;
	std::string menuName;
	
public:
	ListMenu(std::string menuName, std::vector<std::string> options) : menuName{ menuName }, options{ options } {}
	void printStaticMenu(int currentChoice);
	int printDynamicMenu();
	std::string getMenuName();
	void setMenuName(std::string);
	
};

