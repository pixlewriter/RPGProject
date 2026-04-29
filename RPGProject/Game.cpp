#include "Game.h"
#include <iostream>
#include <random>
#include <string>
#include "enterBattle.h"
#include "manageInventory.h"
#include "Menu.h"
#include "Player.h"
#include "IntegerChangeMenu.h"
#include "InventoryItem.h"
#include "audio_manager.h"
#include "TalkingNPC.h"

using namespace std;

bool Game::returnToOverworld() {
	std::cout << "[Action] Returning to the overworld...\n";
    return true;
}

void Game::enterShop() {
    start_music("shop_music.wav", true);
    std::cout << "\033[2J\033[1;1H";
    std::cout << "You walk up to a burly man in a road side trade stand." << endl;
    std::cout << "One empty eye socket looks back at you before he says anything." << endl;
    Order order;
    for (int i = 0; i < 5; i++) {
        std::cout << "\"Wha'dyou want?\"" << endl;
        vector<string> options = { "To find your other eye.", "To look at your tools", "To purchase ya flower" };
        ListMenu dialouge1("Dialogue Menu", options);
        int choice = dialouge1.printDynamicMenu();
        std::cout << "\033[2J\033[1;1H";
        switch (choice) {
        case 1:
            cout << "He growls and you walk away knowing your nightmares would not be as pleasent as they normally are." << endl;
            stop_music();
            return;
        case 2: {
            cout << "\"Here you go then!\"" << endl;
            Shop shop(shopType::starter);
            order = shop.displayShopMenu();
            bool successful = player.purchaseOrder(order);
            std::cout << "\033[2J\033[1;1H";
            if (!successful)
                cout << "Purchase order exceeds weight cap or gold." << endl;
            else {
                cout << "You purchased x" << order.number << " " << order.item.name << " for a total cost of " << order.item.price * order.number << " gold." << endl;
            }
            stop_music();
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

void Game::chat(Player* player, WASDNode& location) {
  /*
    std::cout << "[Action] Starting a conversation with an NPC...\n";

    default_random_engine engine{ static_cast<unsigned>(time(0)) };
    uniform_int_distribution<unsigned> randomInt{ 1,2 };
    unsigned decisionMaker = randomInt(engine);

    if (decisionMaker == 1) {
        roomMateNPC* roomMate = new roomMateNPC();
        roomMate->printDialogue(0);
        delete roomMate;
    }
    else {
    */
    if (location.data == "Cafe") {
        player->alanEncounter = 1;
        hostileGuyNPC* jerk = new hostileGuyNPC();
        jerk->printDialogue(0, player);
        delete jerk;
    }
    else if (location.data == "Egan") {
        englishProfessorNPC* teacher = new englishProfessorNPC();
        teacher->printDialogue(0, player);
        delete teacher;
    }
    else {
      std::cout << "There is no one here to talk to" << std::endl;
    }

}

void Game::startGame() {
    vector<string> startOptions = { "New Game", "Quit Game" };
    ListMenu startMenu = { "Start Menu", startOptions };
    int startChoice = startMenu.printDynamicMenu();

    switch (startChoice) {
    case 1:
        
        return;
    case 2:
        terminate();
    }
}

void Game::quitGame() {
    std::cout << "[Action] Exiting game. Goodbye!\n";
    terminate();
}

void Game::generateRace() {
    cout << "Pick the stats for your character. You have 10 skill points." << endl;
    player.generateStats(10);
    cout << endl;

    vector<string> raceOptions = { "Biology", "Mechanical Engineer", "Computer Science", "English", "Theology", "Buisness"};
    ListMenu raceMenu = { "Majors", raceOptions };
    int raceChoice = raceMenu.printDynamicMenu();

    switch (raceChoice) {
    case 1: // biology
        player.increaseStat(Player::ABBILITY::str, 2);
        player.increaseStat(Player::ABBILITY::con, 2);
        break;
    case 2: // Mechanical Engineer
        player.increaseStat(Player::ABBILITY::con, 2);
        player.increaseStat(Player::ABBILITY::dex, 2);
        break;
    case 3: // Computer Science
        player.increaseStat(Player::ABBILITY::all, 2);
        break;
    case 4:// English
        player.increaseStat(Player::ABBILITY::inte, 4);
        break;
    case 5:// English
        player.increaseStat(Player::ABBILITY::chars, 4);
        break;
    case 6:
        player.increaseStat(Player::ABBILITY::all, -1);
        break;
    }

    cout << endl;
}

/*
void Game::generatePlayerInventory() {
    list<InventoryItem> inventory = generateInventory();
    for (InventoryItem item : inventory) {
        player.addToInventory(item);
    }
}
*/

bool Game::displayOptions(WASDNode& location) {
    int choice = 0;
    bool running = true;
    while (running) {
        vector<string> options = { "Return to Game", "Enter Battle", "Manage Inventory", "Enter Shop", "Talk to Someone", "Quit Game" };
        //cout << location.data << endl;
        bool shopLocation = !(location.data != "JC" && location.data != "Cafe");
        if (!shopLocation) {
            options.erase(options.begin() + 3);
        }
        ListMenu settingsMenu{ "ACTION MENU", options };
        int choice = settingsMenu.printDynamicMenu();
        if (choice > 3 && !shopLocation) choice++;
        //handles valid inputs
        switch (choice) {
        case 1:
            return returnToOverworld();
        case 2:
            //use location?
            enterBattle(&player, &location);
            break;
        case 3:
            manageInventory(&player);
            break;
        case 4:
            enterShop();
            break;
        case 5:
            chat(&player, location);

            if (player.alanEncounter == 1)
            {
                enterBattle(&player, &location);
                player.alanEncounter = 0;
            }
            break;
        case 6:
            quitGame();
            running = false; //ends loop
            break;
        default:
            std::cout << "Invalid selection. Please try again.\n";
        }
    }
    return false;
}

WASDNode* Game::buildMap() {
    WASDNode* CODA    = new WASDNode("Coda");
    WASDNode* Egan    = new WASDNode("Egan");
    WASDNode* CTT     = new WASDNode("CTT");
    WASDNode* Gym     = new WASDNode("Gym");
    WASDNode* JC      = new WASDNode("JC");
    WASDNode* Cafe    = new WASDNode("Cafe");
    WASDNode* Chapel  = new WASDNode("Chapel");
    WASDNode* Library = new WASDNode("Library");

    CODA->a = Egan;
    CODA->w = JC;
    CODA->d = Library;

    CTT->w = Gym;
    CTT->d = JC;
    CTT->s = Egan;

    Cafe->w = JC;
    Cafe->s = Chapel;

    Chapel->w = Cafe;
    Chapel->s = Library;

    Egan->w = CTT;
    Egan->s = CODA;

    Gym->a = CTT;
    Gym->d = JC;

    JC->w = Gym;
    JC->a = CTT;
    JC->s = CODA;
    JC->d = Cafe;

    Library->a = CODA;
    Library->d = Chapel;

    return JC;
}

void Game::gameSetup() {
    this->location = buildMap();
    generateRace();
}

bool Game::gameLoop() {
    start_music("map_music1.wav", true);
    this->location =  Map::getLocation(location);
    stop_music();
    std::cout << "\033[2J\033[1;1H";
    while (displayOptions(*location)) {
        start_music("map_music1.wav", true);
        location = Map::getLocation(location);
        stop_music();
        std::cout << "\033[2J\033[1;1H";
    }
    terminate();
    return false;
}

void Game::run() {
    init_audio();
    startGame();
    play_effect("start3.wav");
    gameSetup();
    openingCutscene();

    while (gameLoop());
}

void Game::terminate() {
    cleanup_audio();
    std::exit(0);
}

void Game::openingCutscene() {
  roomMateNPC* roommate = new roomMateNPC;
  roommate->printDialogue(0);

  cout << "You take a large drink from the glass. It's not too bad. And you do feel better.";
  cout << "\n\nYou feel so good that you wonder if perhaps the world could use you. Maybe there are people out there in desparate need of help. ";
  cout << "You head off toward the JC to see if you're newfound energy is needed..."<< endl;


  vector<string> options{ "Press enter to continue" };
  ListMenu noChoice(" ", options);
  int choice = noChoice.printDynamicMenu();
  cout << "\033[2J\033[1;1H";
}