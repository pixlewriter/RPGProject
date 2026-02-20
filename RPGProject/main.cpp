#include <iostream>
#include <string>
#include "enterBattle.h"
#include "Menu.h"
#include "Player.h"
#include "IntegerChangeMenu.h"

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

    //vector<string> classOptions = { "Fighter", "Wizard", "Rouge"};
    //Menu classMenu = { "Player Class", classOptions };
    //int classChoice = classMenu.printDynamicMenu();
    //
    //switch (classChoice) {
    //case 1: // Fighter is 100 health, 20 attack, no mana
    //    player = { 100,20,0 };
    //    break;
    //case 2: // Wizard is 50 health, 5 attack, 50 mana
    //    player = { 50,5,50 };
    //    break;
    //case 3: // Rouge is 60 health, 10 attack, 20 mana
    //    player = { 60,10,20 };
    //    break;
    //}

    player.generateStats(10);
    cout << endl;

    vector<string> raceOptions = { "Orc", "Dwarf", "Elf", "Human" };
    ListMenu raceMenu = { "Race Class", raceOptions };
    int raceChoice = raceMenu.printDynamicMenu();

    switch (raceChoice) {
    case 1: // orc
        player.increaseStat(Player::ABBILITY::str, 2);
        player.increaseStat(Player::ABBILITY::con, 1);
        break;
    case 2: // If Dwarf, increase helath by 50, stregnth by 10, and decrease mana by 30
        player.increaseStat(Player::ABBILITY::con, 2);
        player.increaseStat(Player::ABBILITY::wis, 1);
        break;
    case 3: // If Elf, decrease health by 10 and increase mana by 30
        player.increaseStat(Player::ABBILITY::dex, 2);
        player.increaseStat(Player::ABBILITY::inte, 1);
        break;
    case 4:// If Human increase all stats by 10
        player.increaseStat(Player::ABBILITY::all, 1);
        break;
    }

    cout << endl;

    while (running) {
        vector<string> options= {"Return to Game", "Enter Battle", "Manage Inventory", "Enter Shop", "Talk to Someone", "Quit Game"};
        ListMenu settingsMenu{ "GAME MENU", options };
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