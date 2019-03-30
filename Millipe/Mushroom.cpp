#include "Mushroom.h"

#include <Arduboy2.h>

#include "Globals.h"

void Mushroom::draw()
{
	Sprites::drawSelfMasked(this->x, this->y, Tiles, (2 - this->h));
}

void Mushroom::damage()
{
	if (this->h > 0)
	{
		--this->h;

		sound.noTone();
		sound.tone(NOTE_G2, 50);
	}
	else
	{
		sound.noTone();
		sound.tone(NOTE_G3, 50);

		this->active = false;
		points += 5;
	}
}