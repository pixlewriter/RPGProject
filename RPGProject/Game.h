#include "Player.h"
#include "Map.h"

#pragma once

class Game
{
private:
	Player player;
	void returnToOverworld();
	void enterShop();
	void chat();
	void quitGame();
	void generateRace();
	void generatePlayerInventory();
	void displayOptions(WASDNode&);
	WASDNode* buildMap();
	void displayKeys();
public:
	Game(Player& player) :player{ player } {}
	void gameSetup();
	bool gameLoop();
	void run();
	void terminate();

};

