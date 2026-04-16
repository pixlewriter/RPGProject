#include <string>
#pragma once
struct WASDNode {
    std::string data;
    WASDNode* w = nullptr;
    WASDNode* a = nullptr;
    WASDNode* s = nullptr;
    WASDNode* d = nullptr;

    WASDNode (std::string name) {
        data = name;
    }
};

class Map
{
private:
	static std::string hexToForgroundColor(std::string hex);
	static std::string hexToBackgroundColor(std::string hex);
public:
    static void printMap(std::string name);
    static WASDNode* getLocation(WASDNode* location);
};

