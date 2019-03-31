#pragma once

//
// MIT License
//
// Copyright (c) 2018-2019 Thomas Buckland (@Dreamer2345)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

//
// Reformatted by Pharap
//

#include "Constants.h"
#include "Globals.h"
#include "HelperFunctions.h"

#include <stddef.h>
#include <stdint.h>

uint8_t length = 5;
uint8_t level = 0;
bool showarrow;

void initialiseLevel()
{
	player.h = 5;
	points = 0;
	level = 0;

	for (uint8_t j = 0; j < maxMushroomsStart; j++)
	{
		uint8_t x;
		uint8_t y;
		bool Done = false;
		while (!Done)
		{
			y = (8 * random(0, 8));
			x = (8 * random(3, 14));
			Done = true;
			for (uint8_t i = 0; i < maxMushroomsStart; ++i)
			{
				if (mushrooms[i].isActive() && (x == mushrooms[i].getX()) && (y == mushrooms[i].getY()))
				{
					Done = false;
					break;
				}
			}
		}
		mushrooms[j].set(x, y);
	}
}

void startNewLevel()
{
	for (uint8_t i = 0; i < maxCentipedeSegments; i++)
		centipedeSegments[i].kill();

	uint8_t leng = (length + level);
	if (leng >= maxCentipedeSegments)
		leng = maxCentipedeSegments;

	const uint8_t y = (8 * random(0, 8));
	for (uint8_t i = 0; i < leng; ++i)
		centipedeSegments[i].set(119, y, (i - 1), (i == 0));

	++level;
}

void initialiseGame()
{
	length = 5;
	initialiseLevel();
	startNewLevel();
	gameState = GameState::Game;
}

void drawCentipede()
{
	for (uint8_t i = 0; i < maxCentipedeSegments; ++i)
		if (centipedeSegments[i].isActive())
				centipedeSegments[i].draw();
}

void updateCentipedeSegments()
{
	for (uint8_t i = maxCentipedeSegments; i > 0; --i)
	{
		const size_t index = (i - 1);
		if (centipedeSegments[index].isActive())
			centipedeSegments[index].update();
	}
}

void updateMainMenu()
{
	Sprites::drawSelfMasked(0, 0, Title, 0);

	if (showarrow)
	{
		Sprites::drawOverwrite(36, 55, Arrow, 0);
	}

	Sprites::drawOverwrite(100, 2, Speaker, arduboy.audio.enabled() ? 1 : 0);

	if (arduboy.justPressed(A_BUTTON))
	{
		sound.noTone();
		sound.tone(NOTE_C5, 50);

		gameState = GameState::Init;
	}

	if (arduboy.justPressed(B_BUTTON))
	{
		bool audio = !arduboy.audio.enabled();

		arduboy.audio.on();
		sound.noTone();
		sound.tone(NOTE_C4, 50);
		arduboy.audio.off();

		if (audio)
			arduboy.audio.on();
		else
			arduboy.audio.off();
	}

	if (arduboy.everyXFrames(15))
	{
		showarrow = !showarrow;
	}
}



void DrawPlayer()
{
	Sprites::drawSelfMasked(0, player.x, Tiles, 3);
}

void Drawbullets()
{
	for (uint8_t i = 0; i < maxbullets; ++i)
		if (bullets[i].isActive())
			bullets[i].draw();
}

void DrawShrooms()
{
	for (uint8_t i = 0; i < maxMushrooms; ++i)
		if (mushrooms[i].isActive())
			mushrooms[i].draw();
}

void updatebullets()
{
	for (uint8_t i = 0; i < maxbullets; ++i)
		if (bullets[i].isActive())
			bullets[i].update();

	for (uint8_t i = 0; i < maxbullets; ++i)
		if (bullets[i].isActive())
			for (uint8_t j = 0; j < maxMushrooms; j++)
				if (mushrooms[j].isActive() && isCollision(mushrooms[j].getX(), mushrooms[j].getY(), bullets[i].getX(), bullets[i].getY()))
				{
					bullets[i].kill();
					mushrooms[j].damage();
					break;
				}

	for (uint8_t i = 0; i < maxbullets; ++i)
		if (bullets[i].isActive())
			for (uint8_t j = 0; j < maxCentipedeSegments; j++)
				if (centipedeSegments[j].isActive() && isCollision(centipedeSegments[j].getX(), centipedeSegments[j].getY(), bullets[i].getX(), bullets[i].getY()))
				{
					bullets[i].kill();
					centipedeSegments[j].damage();

					const uint8_t next = (j + 1);
					if (next != maxCentipedeSegments)
					{
						centipedeSegments[next].setHead(true);
						centipedeSegments[next].toggleDirection();
					}

					break;
				}
}

void drawLevelAndPoints()
{
	arduboy.print(F("Level:"));
	arduboy.println(level);

	arduboy.print(F("Points:"));
	arduboy.println(points);
}

void LevelScreen()
{
	drawLevelAndPoints();

	if(arduboy.everyXFrames(120) || (arduboy.justPressed(A_BUTTON)))
	{
		startNewLevel();
		gameState = GameState::Game;
	}
}

void DeathScreen()
{
	drawLevelAndPoints();

	if(arduboy.justPressed(A_BUTTON))
	{
		gameState = GameState::MainMenu;
	}
}

bool checkAlive()
{
	 for (uint8_t j = 0; j < maxCentipedeSegments; ++j)
		if (centipedeSegments[j].isActive())
			return true;

	return false;
}

void ShowHealth()
{
	for(uint8_t i = 0; i < player.h; ++i)
		Sprites::drawSelfMasked(119, (i * 8), Tiles, 3);
}

void Gameupdate()
{
	player.move();
	updatebullets();

	if(arduboy.everyXFrames(15))
		updateCentipedeSegments();

	DrawShrooms();
	DrawPlayer();
	Drawbullets();
	drawCentipede();
	ShowHealth();

	if (!checkAlive())
	{
		sound.noTone();
		sound.tone(NOTE_C5, 50, NOTE_E5, 50, NOTE_G5, 50);

		gameState = GameState::NextLevel;
	}

	if ((player.h == 0) || (player.h > 5))
	{
		gameState = GameState::Dead;
	}
}