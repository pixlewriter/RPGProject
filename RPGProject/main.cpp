#include <iostream>
#include <string>
#include "enterBattle.h"
#include "Menu.h"

using namespace std;

// function prototypes
void returnToOverworld();
void enterBattle();
void manageInventory();
void enterShop();
void chat();
void quitGame();

int main() {
    int choice = 0;
    bool running = true;


    while (running) {
        vector<string> options= {"Return to Game", "Enter Battle", "Manage Inventory", "Enter Shop", "Talk to Someone", "Quit Game"};
        Menu settingsMenu{ "GAME MENU", options };
        int choice = settingsMenu.printDynamicMenu();
        //handles valid inputs
        switch (choice) {
        case 1:
            returnToOverworld();
            break;
        case 2:
            enterBattle();
            break;
        case 3:
            manageInventory();
            break;
        case 4:
            enterShop();
            break;
        case 5:
            chat();
            break;
        case 6:
            quitGame();
            running = false; //ends loop
            break;
        default:
            std::cout << "Invalid selection. Please try again.\n";
        }
    }

    return 0;
}

//function definitions

void returnToOverworld() {
    std::cout << "[Action] Returning to the overworld...\n";
}

void manageInventory() {
    std::cout << "[Action] Opening inventory management...\n";
}

void enterShop() {
    std::cout << "[Action] Entering the shop menu...\n";
}

void chat() {
    std::cout << "[Action] Starting a conversation with an NPC...\n";
}

void quitGame() {
    std::cout << "[Action] Exiting game. Goodbye!\n";
}