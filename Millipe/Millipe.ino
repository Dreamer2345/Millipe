#include <Arduboy2.h>

#include <stddef.h>
#include <stdint.h>

#include "GameState.h"
#include "Globals.h"
#include "Constants.h"
#include "Bitmaps.h"
#include "Player.h"
#include "Mushroom.h"
#include "Centipede.h"
#include "Game.h"

void setup()
{
	arduboy.boot();
	arduboy.flashlight();
	arduboy.audio.begin();
	arduboy.clear();
	arduboy.initRandomSeed();

	Sprites::drawSelfMasked(centreX - 26, centreY - 17, MainLogo, 0);
	arduboy.display();
	delay(1000);
}

void loop()
{
	if(!arduboy.nextFrame())
		return;

	arduboy.pollButtons();
	arduboy.clear();

	switch(gameState)
	{
		case GameState::Game:
			Gameupdate();
			break;

		case GameState::Init:
			initialiseGame();
			break;

		case GameState::NextLevel:
			LevelScreen();
			break;

		case GameState::MainMenu:
			updateMainMenu();
			break;

		case GameState::Dead:
			DeathScreen();
			break;
	}

	arduboy.display();
}