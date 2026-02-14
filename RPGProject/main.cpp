#include <iostream>
#include <string>
#include "enterBattle.h"
#include "manageInventory.h"


// function prototypes
void returnToOverworld();
void enterBattle();
void manageInventory();
void enterShop();
void chat();
void quitGame();
void displayMenu();

int main() {
    int choice = 0;
    bool running = true;

    while (running) {
        displayMenu();
        std::cout << "Enter your choice: ";

        // stops bad inputs
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
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

void displayMenu() {
    std::cout << "\n--- GAME MENU ---\n";
    std::cout << "1. Return to Game\n";
    std::cout << "2. Enter Battle\n";
    std::cout << "3. Manage Inventory\n";
    std::cout << "4. Enter Shop\n";
    std::cout << "5. Talk to Someone\n";
    std::cout << "6. Quit Game\n";
    std::cout << "-----------------\n";
}

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