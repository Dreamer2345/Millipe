#include "Centipede.h"

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
#include "Bitmaps.h"
#include "HelperFunctions.h"

static bool canMoveTo(uint8_t x, uint8_t y)
{
	if (((y + 8) > 64) || (y > 64))
		return false;

	if (x == 0)
		return false;

	for (uint8_t j = 0; j < maxMushrooms; ++j)
		if (mushrooms[j].isActive() && isCollision(mushrooms[j].getX(), mushrooms[j].getY(), x, y))
			return false;

	return true;
}

void CentipedeSegment::draw()
{
	Sprites::drawSelfMasked(x, y, Tiles, (this->head) ? 4 : 5);
}

void CentipedeSegment::damage()
{
	this->active = false;

	sound.noTone();
	sound.tone(NOTE_E3H, 50);

	for(uint8_t i = 0; i < maxMushrooms; ++i)
	{
		if (!mushrooms[i].isActive())
		{
			mushrooms[i].set((x + 1), y);
			break;
		}
	}

	points += 30;
}

void CentipedeSegment::update()
{
	if (!this->head)
	{
		this->x = centipedeSegments[this->parent].getX();
		this->y = centipedeSegments[this->parent].getY();
		this->direction = centipedeSegments[this->parent].getDirection();
		return;
	}

	bool hasMoved = false;
	if (this->direction == Direction::North)
	{
		if (canMoveTo(this->x, this->y - 8))
		{
			this->y -= 8;
			hasMoved = true;
		}
	}
	else
	{
		if (canMoveTo(this->x, this->y + 8))
		{
			this->y += 8;
			hasMoved = true;
		}
	}

	if(!hasMoved)
	{
		if (canMoveTo(this->x - 8, this->y))
			this->x -= 8;

		this->toggleDirection();
	}

	if ((this->x > 119) || (this->x == 0))
	{
		this->x = ((WIDTH - 1) - 8);
		--player.h;
		this->toggleDirection();
	}

	if (!canMoveTo(this->x - 8, y))
	{
		const uint8_t upY = (this->y - 8);
		const uint8_t downY = (this->y + 8);

		while (!canMoveTo(this->x, downY) && !canMoveTo(this->x, upY))
			this->x += 8;
	}
}