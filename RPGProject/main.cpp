#include <iostream>
#include <string>
#include <random>
#include "enterBattle.h"
#include "manageInventory.h"
#include "Menu.h"
#include "Player.h"
#include "IntegerChangeMenu.h"
#include "InventoryItem.h"
#include "Game.h"


#include "audio_manager.h"

using namespace std;

int main() {
	Player player;
	Game game{ player };
	game.run();
}
