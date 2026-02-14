#include <iostream>
#include <string>
#include "enterBattle.h"
#include "Menu.h"
#include "Player.h"

using namespace std;
#include "audio_manager.h"

// function prototypes
void returnToOverworld();
void manageInventory();
void enterShop();
void chat();
void quitGame();

int main() {
    init_audio();
    int choice = 0;
    bool running = true;

    Player player;

    vector<string> classOptions = { "Fighter", "Wizard", "Rouge"};
    Menu classMenu = { "Player Class", classOptions };
    int classChoice = classMenu.printDynamicMenu();
    
    switch (classChoice) {
    case 1: // Fighter is 100 health, 20 attack, no mana
        player = { 100,20,0 };
        break;
    case 2: // Wizard is 50 health, 5 attack, 50 mana
        player = { 50,5,50 };
        break;
    case 3: // Rouge is 60 health, 10 attack, 20 mana
        player = { 60,10,20 };
        break;
    }

    vector<string> raceOptions = { "Orc", "Dwarf", "Elf", "Human" };
    Menu raceMenu = { "Race Class", raceOptions };
    int raceChoice = raceMenu.printDynamicMenu();

    switch (raceChoice) {
    case 1: // If orc, increase health by 30, strength by 10, and decrease mana by 10
        player.setMaxHealth(player.getMaxHealth() + 30);
        player.setTempHealth(player.getMaxHealth());
        player.setStrength(player.getStrength() + 10);
        player.setMana(player.getMana() - 10);
        break;
    case 2: // If Dwarf, increase helath by 50, stregnth by 10, and decrease mana by 30
        player.setMaxHealth(player.getMaxHealth() + 50);
        player.setTempHealth(player.getMaxHealth());
        player.setStrength(player.getStrength() + 10);
        player.setMana(player.getMana() - 30);
        break;
    case 3: // If Elf, decrease health by 10 and increase mana by 30
        player.setMaxHealth(player.getMaxHealth() - 10);
        player.setTempHealth(player.getMaxHealth());
        // no strength change
        player.setMana(player.getMana() + 30);
        break;
    case 4:// If Human increase all stats by 10
        player.setMaxHealth(player.getMaxHealth() + 10);
        player.setTempHealth(player.getMaxHealth());
        player.setStrength(player.getStrength() + 10);
        player.setMana(player.getMana() + 10);
        break;
    }

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
            enterBattle(&player);
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
    cleanup_audio();
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