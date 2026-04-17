#include "Player.h"
#include "Map.h"

#pragma once

class Game
{
private:
	Player player;
	bool returnToOverworld();
	void enterShop();
	void chat(Player*);
	void quitGame();
	void generateRace();
	void generatePlayerInventory();
	bool displayOptions(WASDNode&);
	WASDNode* buildMap();
	void displayKeys();
public:
	Game(Player& player) :player{ player } {}
	void gameSetup();
	bool gameLoop();
	void run();
	void terminate();

};

