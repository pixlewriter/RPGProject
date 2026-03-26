#include <iostream>
#include <string>
#include "enterBattle.h"
#include "manageInventory.h"
#include "Menu.h"
#include "Player.h"
#include "IntegerChangeMenu.h"
#include "InventoryItem.h"

using namespace std;
#include "audio_manager.h"

// function prototypes
void returnToOverworld();
void enterShop(Player& player);
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
    //give the player an inventory
    /*
    list<InventoryItem> inventory = generateInventory();
        for (InventoryItem item : inventory) {
            player.addToInventory(item);
    }*/

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
            manageInventory(&player);
            break;
        case 4:
            enterShop(player);
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

void enterShop(Player& player) {
    std::cout << "\033[2J\033[1;1H";
    std::cout << "You walk up to a burly man in a road side trade stand." << endl;
    std::cout << "One empty eye socket looks back at you before he says anything." << endl;
    Order order;
    for (int i = 0; i < 5; i++) {
        std::cout << "\"Wha'dyou want?\"" << endl;
        vector<string> options = {"To find your other eye.", "To look at your tools", "To purchase ya flower"};
        ListMenu dialouge1("Dialogue Menu",options);
        int choice = dialouge1.printDynamicMenu();
        std::cout << "\033[2J\033[1;1H";
        switch (choice) {
        case 1:
            cout << "He growls and you walk away knowing your nightmares would not be as pleasent as they normally are." << endl;
            return;
        case 2: {
            cout << "\"Here you go then!\"" << endl;
            Shop shop(shopType::starter);
            cout << "Gold: " << player.seeGold() << endl;
            cout << "Weight: " << player.seeWeight() << "/200" << std::endl;
            order = shop.displayShopMenu();
            bool successful = player.purchaseOrder(order);
            std::cout << "\033[2J\033[1;1H";
            if (!successful)
                cout << "Purchase order exceeds weight cap or gold." << endl;
            else {
                cout << "You purchased x" << order.number << " " << order.item.name << " for a total cost of " << order.item.price * order.number << " gold." << endl;
            }
            return;
        }
        case 3: {
            if (i == 0) {
                cout << "He looks confused at your odd question and then gestures at the surrounding pansies." << endl;
            }
            else if (i == 4) {
                cout << "His eyes light up. \"Ahhh yes my flower\". He winks and pulls out something from under his kart" << endl;
                Shop shop(std::vector<InventoryItem>({ InventoryItem("Bread",10, 1) }));
                order = shop.displayShopMenu();
                player.purchaseOrder(order);
                std::cout << "\033[2J\033[1;1H";
                cout << "You purchased x" << order.number << " " << order.item.name << " for a total cost of " << order.item.price * order.number << " gold." << endl;
            }
            else {
                cout << "He looks confused and insists he doesn't know what your talking about." << endl;
            }
            break;
        }
        }
    }
}

void chat() {
    std::cout << "[Action] Starting a conversation with an NPC...\n";
}

void quitGame() {
    std::cout << "[Action] Exiting game. Goodbye!\n";
}