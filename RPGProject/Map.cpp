#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip> 
#include <conio.h>
#include <format>

using namespace std;

std::string Map::hexToForgroundColor(std::string hex) {
    unsigned int r, g, b;
    std::stringstream ss;
    ss << std::hex << hex.substr(1, 2); ss >> r;
    ss.clear(); ss << std::hex << hex.substr(3, 2); ss >> g;
    ss.clear(); ss << std::hex << hex.substr(5, 2); ss >> b;

    // ANSI TrueColor (24-bit) escape sequence
    return "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::string Map::hexToBackgroundColor(std::string hex) {
    unsigned int r, g, b;
    std::stringstream ss;
    ss << std::hex << hex.substr(1, 2); ss >> r;
    ss.clear(); ss << std::hex << hex.substr(3, 2); ss >> g;
    ss.clear(); ss << std::hex << hex.substr(5, 2); ss >> b;

    // ANSI TrueColor (24-bit) escape sequence
    return "\x1b[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

void Map::printMap(std::string name) {
    std::cout << "\033[2J\033[1;1H";
    std::string fileName = "WorldMap-" + name + ".csv";
    std::string filePath = "./CSVFiles/" + fileName;
    std::ifstream file(filePath);// Open the CSV file
    // If the absolute path fails, try a relative-path fallback to the project's CSVFiles folder
    if (!file.is_open()) {
        std::string altPath = "CSVFiles/" + fileName;
        file.open(altPath);
        if (!file.is_open()) {
            std::cerr << "Failed to open CSV file at: " << filePath << " or " << altPath << "\n";
            return;
        }
    }
    std::string line;

    // Skip the header line (optional, if your file has one)
    if (!std::getline(file, line)) {
        // file is empty
        std::cerr << "CSV file is empty: " << fileName << "\n";
        file.close();
        return;
    }
    int x;
    int y = -1;
    while (std::getline(file, line)) {
        std::stringstream ss(line); // Create a stringstream from the line
        std::string field;

        char ASCII;
        std::string forground;
        std::string background;



        // Extract fields using comma as a delimiter
        if (std::getline(ss, field, ',')) {
            x = std::stoi(field);
        }
        if (std::getline(ss, field, ',')) {
            if (std::stoi(field) > y) {
                std::cout << std::endl;
            }
            y = std::stoi(field); // Convert string to int
        }
        if (std::getline(ss, field, ',')) {
            ASCII = std::stoi(field);
        }
        if (std::getline(ss, field, ',')) {
            forground = field;
        }
        if (std::getline(ss, field, ',')) {
            background = field;
        }
        std::cout << hexToForgroundColor(forground) << hexToBackgroundColor(background) << ASCII << "\x1b[0m";
    }
    std::cout << std::endl;

    file.close();
}

WASDNode* Map::getLocation(WASDNode* location) {
    printMap(location->data);
    while (true) {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
            case 'w':
                if (location->w != nullptr) return getLocation(location->w);
                break;
            case 'a':
                if (location->a != nullptr) return getLocation(location->a);
                break;
            case 's':
                if (location->s != nullptr) return getLocation(location->s);
                break;
            case 'd':
                if (location->d != nullptr) return getLocation(location->d);
                break;
            case 13:
                return location;

            }
        }
    }
}